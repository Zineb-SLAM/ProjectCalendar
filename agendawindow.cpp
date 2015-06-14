#include "agendawindow.h"
#include "window.h"
#include"show_info.h"



AgendaWindow::AgendaWindow() :
    TM(TacheManager::getInstance()), PM(ProjetManager::getInstance()), ProgM(ProgrammationManager::getInstance())
{



    jours = new QHBoxLayout;
    heures = new QVBoxLayout;
    emploi_du_temps = new QVBoxLayout;
    semaine = new QHBoxLayout;
    agenda = new QHBoxLayout;
    general = new QVBoxLayout;

    //couche jours
    lundi = new QLabel("lundi", this);
    mardi = new QLabel("mardi", this);
    mercredi = new QLabel("mercredi", this);
    jeudi = new QLabel("jeudi", this);
    vendredi = new QLabel("vendredi", this);
    samedi = new QLabel("samedi", this);
    dimanche = new QLabel("dimanche", this);
    jours->addWidget(lundi);
    jours->addWidget(mardi);
    jours->addWidget(mercredi);
    jours->addWidget(jeudi);
    jours->addWidget(vendredi);
    jours->addWidget(samedi);
    jours->addWidget(dimanche);

    //couche heures
    label_00h = new QLabel("00h", this);
    label_01h = new QLabel("01h", this);
    label_02h = new QLabel("02h", this);
    label_03h = new QLabel("03h", this);
    label_04h = new QLabel("04h", this);
    label_05h = new QLabel("05h", this);
    label_06h = new QLabel("06h", this);
    label_07h = new QLabel("07h", this);
    label_08h = new QLabel("08h", this);
    label_09h = new QLabel("09h", this);
    label_10h = new QLabel("10h", this);
    label_11h = new QLabel("11h", this);
    label_12h = new QLabel("12h", this);
    label_13h = new QLabel("13h", this);
    label_14h = new QLabel("14h", this);
    label_15h = new QLabel("15h", this);
    label_16h = new QLabel("16h", this);
    label_17h = new QLabel("17h", this);
    label_18h = new QLabel("18h", this);
    label_19h = new QLabel("19h", this);
    label_20h = new QLabel("20h", this);
    label_21h = new QLabel("21h", this);
    label_22h = new QLabel("22h", this);
    label_23h = new QLabel("23h", this);
    heures->addWidget(label_00h);
    heures->addWidget(label_01h);
    heures->addWidget(label_02h);
    heures->addWidget(label_03h);
    heures->addWidget(label_04h);
    heures->addWidget(label_05h);
    heures->addWidget(label_06h);
    heures->addWidget(label_07h);
    heures->addWidget(label_08h);
    heures->addWidget(label_09h);
    heures->addWidget(label_10h);
    heures->addWidget(label_11h);
    heures->addWidget(label_12h);
    heures->addWidget(label_13h);
    heures->addWidget(label_14h);
    heures->addWidget(label_15h);
    heures->addWidget(label_16h);
    heures->addWidget(label_17h);
    heures->addWidget(label_18h);
    heures->addWidget(label_19h);
    heures->addWidget(label_20h);
    heures->addWidget(label_21h);
    heures->addWidget(label_22h);
    heures->addWidget(label_23h);


    //couche emploi du temps
    scene = new CustomQGraphicsScene();
    scene->setSceneRect(0,0,700,600);
    visu = new QGraphicsView(scene);
    //visu->setSceneRect(0,12.5,700,600);
    visu->show();
    emploi_du_temps->addItem(jours);
    emploi_du_temps->addWidget(visu);

    //couche semaine
    spacer_semaine = new QSpacerItem(50,0,QSizePolicy::Expanding,QSizePolicy::Preferred);
    s = new QLabel("Semaine", this);
    choix_semaine = new QSpinBox(this);
    choix_semaine->setRange(1,53);
    a = new QLabel("Annee", this);
    choix_annee = new QSpinBox(this);
    choix_annee->setRange(2015,3000);
    semaine->addItem(spacer_semaine);
    semaine->addWidget(s);
    semaine->addWidget(choix_semaine);
    semaine->addWidget(a);
    semaine->addWidget(choix_annee);

    //couche agenda
    spacer = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Preferred);
    spacer2 = new QSpacerItem(20,0,QSizePolicy::Preferred, QSizePolicy::Preferred);
    agenda->addItem(spacer);
    agenda->addItem(heures);
    agenda->addItem(spacer2);
    agenda->addItem(emploi_du_temps);

    //fenêtre principale
    widget_central = new QWidget(this);
    general->addItem(semaine);
    general->addItem(agenda);
    widget_central->setLayout(general);

    setCentralWidget(widget_central); //place le widget central

    //dock
    projets = new QDockWidget(this);
    projets->setWindowTitle("Projets"); //donne un titre au dock
    liste_projets = new QTextEdit(this);
    liste_projets->textCursor().insertText(PM.afficherTitreProjets()+"\n");
    liste_projets->setReadOnly(1); //en lecture seulement
    addDockWidget(Qt::LeftDockWidgetArea,projets);
    projets->setWidget(liste_projets);

    taches = new QDockWidget(this);
    taches->setWindowTitle("Taches à programmer");
    liste_taches = new QTextEdit(this);
    liste_taches->textCursor().insertText(TM.afficherTachesAProgrammer());
    liste_taches->setReadOnly(1);

    addDockWidget(Qt::LeftDockWidgetArea, taches);
    taches->setWidget(liste_taches);

    connect(choix_semaine, SIGNAL(valueChanged(int)), this, SLOT(changer_semaine()));
    connect(choix_annee, SIGNAL(valueChanged(int)), this, SLOT(changer_semaine()));

    createActions();
    createMenus();

   QMessageBox message;
   message.setText("Hello World Calendar!");
    message.exec();


}

void AgendaWindow::createActions() {
    charger = new QAction("Charger",this);
    connect(charger, SIGNAL(triggered()), this, SLOT(charger_agenda()));

    exporter = new QAction("Exporter en XML",this);
    connect(exporter, SIGNAL(triggered()), this, SLOT(sauvegarder_agenda()));

    exporterTxt = new QAction("Exporter en txt", this);
    connect(exporterTxt, SIGNAL(triggered()), this, SLOT(sauvegarder_txt()));

    programmer_tache = new QAction("Programmer",this);
    connect(programmer_tache, SIGNAL(triggered()), this, SLOT(demander_programmer()));

    creer_projet = new QAction("Creer un projet", this);
    connect(creer_projet, SIGNAL(triggered()), this, SLOT(ajouter_projet()));

    creer_tache = new QAction("Creer une tache", this);
    connect(creer_tache, SIGNAL(triggered()), this, SLOT(ajouter_tache()));

    Ajouter_tache_a_composite= new QAction("Ajouter Tache a composite", this);
    connect(Ajouter_tache_a_composite, SIGNAL(triggered()), this, SLOT(ajouter_tache_a_composite()));

    Ajouter_Precedence=new QAction("Ajouter Precedence", this);
    connect(Ajouter_Precedence, SIGNAL(triggered()), this, SLOT(ajouter_precedence()));

    creer_activite = new QAction("Creer une activite", this);
    connect(creer_activite, SIGNAL(triggered()), this, SLOT(ajouter_activite()));

    Rechercher_Projet=new QAction("Rechercher un  Projet", this);
    connect(Rechercher_Projet, SIGNAL(triggered()), this, SLOT(recherche_projet()));

    Ajouter_tache_a_projet=new QAction("Ajouter Tache a Projet", this);
    connect(Ajouter_tache_a_projet, SIGNAL(triggered()), this, SLOT(ajouter_tache_a_projet()));

    Rechercher_Tache=new QAction("Rechercher Une Tache", this);
    connect(Rechercher_Tache, SIGNAL(triggered()), this, SLOT(recherche_tache()));

    Rechercher_Programmation=new QAction("Rechercher Un Evenement", this);
    connect(Rechercher_Programmation, SIGNAL(triggered()), this, SLOT(recherche_programmation()));

    Afficher_projets=new QAction("Afficher Projets", this);
    connect(Afficher_projets, SIGNAL(triggered()), this, SLOT(afficher_projets()));

    Supprimer_tache=new QAction("Supprimer Tache", this);
    connect(Supprimer_tache, SIGNAL(triggered()), this, SLOT(supprimer_tache()));

    Supprimer_projet=new QAction("Supprimer Projet", this);
    connect(Supprimer_projet, SIGNAL(triggered()), this, SLOT(supprimer_projet()));

    Afficher_taches=new QAction("Afficher Taches", this);
    connect(Afficher_taches, SIGNAL(triggered()), this, SLOT(afficher_taches()));

    Supprimer_activite=new QAction("Supprimer Activité", this);
    connect(Supprimer_activite, SIGNAL(triggered()), this, SLOT(supprimer_activite()));

    Schedule=new QAction("Affichage des Programmations",this);
    connect(Schedule,SIGNAL(triggered()),this,SLOT(afficher_schedule()));
}

void AgendaWindow::createMenus() {
    menu_options = menuBar()->addMenu("Options");;
    menu_options->addAction(charger);
    menu_options->addAction(exporter);
    //menu_options->addAction(exporter_txt);
    menu_options->addAction(exporterTxt);

    menu_tache = menuBar()->addMenu("Tache");
    menu_tache->addAction(creer_tache);
    menu_tache->addAction(Ajouter_tache_a_composite);
    menu_tache->addAction(Ajouter_Precedence);
    menu_tache->addAction(programmer_tache);
    menu_tache->addAction(Supprimer_tache);


    menu_projet = menuBar()->addMenu("Projet");
    menu_projet->addAction(creer_projet);
    menu_projet->addAction(Ajouter_tache_a_projet);
    menu_projet->addAction(Supprimer_projet);

    menu_activite = menuBar()->addMenu("Activite");
    menu_activite->addAction(creer_activite);
    menu_activite->addAction(Supprimer_activite);

    menu_activite = menuBar()->addMenu("Rechercher");
    menu_activite->addAction(Rechercher_Projet);
    menu_activite->addAction(Rechercher_Tache);
    menu_activite->addAction(Rechercher_Programmation);

    menu_arbre = menuBar()->addMenu("Arborescence");
    menu_arbre->addAction(Afficher_projets);
    menu_arbre->addAction(Afficher_taches);
    menu_arbre->addAction(Schedule);
}

//fonctions des slots

void AgendaWindow::changer_semaine() {
    //préparation de la scène
    scene->clear();
    scene->update();
    int s = choix_semaine->value();
    int a = choix_annee->value();
    //pour chaque tache programmée, on vérifie qu'elle correspond à la même semaine et même année que les valeurs récupérées
    for(std::vector<Programmation *>::iterator it = ProgM.getTabprogs().begin(); it != ProgM.getTabprogs().end(); it++) {
        int temp = (*it)->getDate().getAnnee();
        int *year = &temp;
        if((s == (*it)->getDate().toQDate().weekNumber(&temp)) && (a == (*it)->getDate().getAnnee()))
            if(!((*it)->getEvent()->cestunetache())) { //si c'est une activité
                Event *temp = const_cast<Event *>((*it)->getEvent());
                placer_evenement(dynamic_cast<Activite *>(temp));
            }
            else { //si c'est une tache
                Event *temp = const_cast<Event *>((*it)->getEvent());
                placer_evenement(dynamic_cast<TacheU *>(temp));
            }
    }
}

void AgendaWindow::placer_evenement(Activite* a) {
    QDate date_prog = ProgM.getProg(a->getId())->getDate().toQDate();
    Programmation* prog = ProgM.trouverProgrammation(a);
    int jour = date_prog.dayOfWeek() - 1; //lundi : 0, mardi : 1...
    qreal x = jour * 100;
    bool sur2Jours = false;
    Horaire *fin = prog->getHoraire().getFin(a->getDuree(), sur2Jours);
    try {
    //si un événement a une durée sur 2 jours, il faut afficher le début sur 1 jour et la suite sur l'autre donc on place 2 blocs
    if (sur2Jours == true) {
        Horaire minuit(0,0);
        Duree *d2 = minuit.entre2(*fin);
        Duree d1(a->getDuree().getDureeEnMinutes() - d2->getDureeEnMinutes()); //a->getDuree() - d2;
        if(a->estUnRdv()) {
            //on crée les 2 parties du rdv
            Rdv *a1 = new Rdv(a->getId(), a->getTitre(), d1, a->getLieu(), "");
            Rdv *a2 = new Rdv(a->getId(), a->getTitre(), *d2, a->getLieu(), "");
            ItemActivite *part1 = new ItemActivite(a1);
            ItemActivite *part2 = new ItemActivite(a2);
            scene->addItem(part1);
            scene->addItem(part2);
            unsigned int debutH = prog->getHoraire().getHeure();
            unsigned int debutM = prog->getHoraire().getMinute();
            int nbMinutesAvant = (60 * debutH) + debutM;
            qreal y = (nbMinutesAvant * 25) / 60;
            part1->setPos(scene->sceneRect().left()+x,scene->sceneRect().top()+y);
            part2->setPos(scene->sceneRect().left()+x+100,scene->sceneRect().top());

        }
        else {
            //on crée les 2 parties de la réunion
            Reunion *a1 = new Reunion(a->getId(), a->getTitre(), d1, a->getLieu());
            Reunion *a2 = new Reunion(a->getId(), a->getTitre(), *d2, a->getLieu());
            ItemActivite *part1 = new ItemActivite(a1);
            ItemActivite *part2 = new ItemActivite(a2);
            scene->addItem(part1);
            scene->addItem(part2);
            unsigned int debutH = prog->getHoraire().getHeure();
            unsigned int debutM = prog->getHoraire().getMinute();
            int nbMinutesAvant = (60 * debutH) + debutM;
            qreal y = (nbMinutesAvant * 25) / 60;
            part1->setPos(scene->sceneRect().left()+x,scene->sceneRect().top()+y);
            part2->setPos(scene->sceneRect().left()+x+100,scene->sceneRect().top());
        }
    }
    else { //sinon on place un seul item
            ItemActivite *activite = new ItemActivite(a);
            unsigned int debutH = prog->getHoraire().getHeure();
            unsigned int debutM = prog->getHoraire().getMinute();
            int nbMinutesAvant = (60 * debutH) + debutM;
            qreal y = (nbMinutesAvant * 25) / 60;
            scene->addItem(activite);
            activite->setPos(scene->sceneRect().left()+x,scene->sceneRect().top()+y);
    }
    } catch (CalendarException ce) {
            QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);
      }
}

void AgendaWindow::placer_evenement(TacheU *t) {
    QDate date_prog = ProgM.getProg(t->getId())->getDate().toQDate();
    Programmation * prog = ProgM.trouverProgrammation(t);
    int jour = date_prog.dayOfWeek() - 1; //lundi : 0, mardi : 1...
    qreal x = jour * 100;
    bool sur2Jours = false;
    Horaire *fin = prog->getHoraire().getFin(t->getDuree(),sur2Jours);
    try { //si un événement a une durée sur 2 jours, il faut afficher le début sur 1 jour et la suite sur l'autre donc on place 2 blocs
        if (sur2Jours == true) {
            //on crée les 2 blocs
            Horaire minuit(0,0);
            Duree *d2 = minuit.entre2(*fin);
            Duree d1(t->getDuree().getDureeEnMinutes() - d2->getDureeEnMinutes());
            TacheU *t1 = TM.ajouterTacheU(t->getId(), t->getTitre(), d1, t->getDisponibilite(), t->getEcheance());
            TacheU *t2 = TM.ajouterTacheU(t->getId(), t->getTitre(), *d2, t->getDisponibilite(), t->getEcheance());
            ItemTache *part1 = new ItemTache(t1);
            ItemTache *part2 = new ItemTache(t2);
            scene->addItem(part1);
            scene->addItem(part2);
            unsigned int debutH = prog->getHoraire().getHeure();
            unsigned int debutM = prog->getHoraire().getMinute();
            int nbMinutesAvant = (60 * debutH) + debutM;
            qreal y = (nbMinutesAvant * 25) / 60;
            part1->setPos(scene->sceneRect().left()+x,scene->sceneRect().top()+y);
            part2->setPos(scene->sceneRect().left()+x+100,scene->sceneRect().top());
        }
        else { //sinon on place un seul bloc
            ItemTache *tache = new ItemTache(t);
            unsigned int debutH = ProgM.trouverProgrammation(t)->getHoraire().getHeure();
            unsigned int debutM = ProgM.trouverProgrammation(t)->getHoraire().getMinute();
            int nbMinutes = (60 * debutH) + debutM;
            qreal y = (nbMinutes * 25) / 60;
            scene->addItem(tache);
            tache->setPos(scene->sceneRect().left()+x,scene->sceneRect().top()+y);
        }
    } catch (CalendarException ce) {
        QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);
        }
}

void AgendaWindow::charger_agenda() {
    QString chemin = QFileDialog::getOpenFileName();
    if (!chemin.isEmpty())
        PM.load(chemin);
}

void AgendaWindow::sauvegarder_agenda() {
    QString chemin = QFileDialog::getSaveFileName();
    if (!chemin.isEmpty())
        PM.save(chemin);
}

void AgendaWindow::sauvegarder_txt() {
    QString chemin = QFileDialog::getSaveFileName();
    if (!chemin.isEmpty())
        PM.saveTxt(chemin);
}

void AgendaWindow::demander_programmer()
{
    bool ok;
    Horaire *h;
    Date *d;
    Duree* dur;
    QString id = QInputDialog::getText(this,"Programmer","Entrez l'id de la tache à programmer :", QLineEdit::Normal,"valeur", &ok);
    try
    {
        if (ok && !id.isEmpty())
        {
            TacheU* t = dynamic_cast<TacheU*>(TM.getTache(id));
            NewProgrammation *fenetre_programmation = new NewProgrammation(this);
            if(fenetre_programmation->exec())
            {
                h = new Horaire(fenetre_programmation->getSchedule().time().hour(), fenetre_programmation->getSchedule().time().minute());
                d = new Date(fenetre_programmation->getDate().date().day(),fenetre_programmation->getDate().date().month(),fenetre_programmation->getDate().date().year());
                dur=new Duree(fenetre_programmation->getDuree().time().hour(),fenetre_programmation->getDuree().time().minute());
               if(t->isPreemptive())
                {
                ProgM.ajouterProgrammation(t,*d,*h,*dur);
                QMessageBox msgBox;
                msgBox.setText("Tache Unitaire Preemtive Programée!");
                msgBox.exec();
               }

                else
                {

                        ProgM.ajouterProgrammation(t,*d,*h);
                        QMessageBox msgBox;
                        msgBox.setText("Tache Unitaire Programée!");
                        msgBox.exec();
                }

            }
        }
    }
    catch (CalendarException ce) {
        QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);
      }
    catch (std::exception e) { QMessageBox::information(0,"Erreur",e.what(),QMessageBox::Ok);}


   }


void AgendaWindow::ajouter_projet() {
    QString *id;
    QString *title;
    Date *disponibility;
    Date *deadline;
    NewProject *fenetre_projet = new NewProject(this);
    try {
        if(fenetre_projet->exec()) {
            id = new QString(fenetre_projet->getId().text());
            title = new QString(fenetre_projet->getTitle().text());
            disponibility = new Date(fenetre_projet->getDisponibility().date().day(), fenetre_projet->getDisponibility().date().month(), fenetre_projet->getDisponibility().date().year());
            deadline = new Date(fenetre_projet->getDeadline().date().day(), fenetre_projet->getDeadline().date().month(), fenetre_projet->getDeadline().date().year());
            PM.creerProjet(*id,*title,*disponibility,*deadline);
            QMessageBox msgBox;
            msgBox.setText("Projet Ajoutee!");
            msgBox.exec();
        }
    } catch (CalendarException ce) {
        QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);
        }
    this->liste_projets->setHtml(PM.afficherTitreProjets()); //mise à jour du texte du dock widget des tâches à programmer

}
void AgendaWindow::ajouter_tache_a_projet()
{
    bool ok,ok2;
    QString id = QInputDialog::getText(this,"Tache","Entrez l'id du Projet :", QLineEdit::Normal,"valeur", &ok);
    QString id2 = QInputDialog::getText(this,"Tache","Entrez l'id de la Tache:", QLineEdit::Normal,"valeur", &ok2);
         try
         {
             if (ok && ok2 && !id.isEmpty() && !id2.isEmpty())
             {
                  Projet* P = PM.getProjet(id);
                  Tache* T=TM.getTache(id2);
                   PM.ajouterTacheAProjet(P,T);//<! ProjetManager gère le Projet donc c'est lui qui appelera la fonction d'ajout dans Projet qui verifira aussi que la tache n'existe pas préalablement dans le projet
                   QMessageBox msgBox;
                   msgBox.setText("Tache Ajoutee a Projet!");
                   msgBox.exec();
             }
          }

         catch (CalendarException ce) {
                 QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);}

             catch (std::exception e) {
                    QMessageBox::information(0,"Erreur",e.what(),QMessageBox::Ok);}
}

void AgendaWindow::ajouter_tache()
{
    QString *id;
    QString *title;
    Duree *duration;
    Date *dispo;
    Date *deadl;
    QString *t;
    bool b;
    NewTask *fenetre_tache = new NewTask(this);
    try {
        if(fenetre_tache->exec())
        {
            id = new QString(fenetre_tache->getId().text());
            title = new QString(fenetre_tache->getTitle().text());
            //h = new Horaire(fenetre_programmation->getSchedule().time().hour(), fenetre_programmation->getSchedule().time().minute());
            //d = new Date(fenetre_programmation->getDate().date().day(),fenetre_programmation->getDate().date().month(),fenetre_programmation->getDate().date().year());
            duration = new Duree(fenetre_tache->getDuration().time().hour(),fenetre_tache->getDuration().time().minute());
            dispo = new Date(fenetre_tache->getDisponibility().date().day(),fenetre_tache->getDisponibility().date().month(),fenetre_tache->getDisponibility().date().year());
            deadl = new Date(fenetre_tache->getDeadline().date().day(),fenetre_tache->getDeadline().date().month(),fenetre_tache->getDeadline().date().year());
            t = new QString(fenetre_tache->getType().currentText());
            b= fenetre_tache->getPreemtive().isChecked();
            if(t == QString("unitaire"))
            {

                TM.ajouterTacheU(*id,*title,*duration,*dispo,*deadl,b);
                QMessageBox msgBox;
                msgBox.setText("Tache Unitaire Ajoutee!");
                msgBox.exec();

            }
            else if (t==QString("composite") && b)
                throw CalendarException("Une Tache Composite n'est pas preemtive");
            else
            {
                TM.ajouterTacheC(*id,*title,*duration,*dispo,*deadl);
                TM.ajouterTacheU(*id,*title,*duration,*dispo,*deadl,b);
                QMessageBox msgBox;
                msgBox.setText("Tache Composite Ajoutee!");
                msgBox.exec();
           // this->liste_taches->setHtml(TM.afficherTachesAProgrammer()); //mise à jour du texte du dock widget des tâches à programmer

            }
        }
    }
    catch (CalendarException ce) {
        QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);
        }
}

 void AgendaWindow::ajouter_precedence()
 {
     bool ok,ok2;
     QString id = QInputDialog::getText(this,"Tache","Entrez l'id de la Tache QUI VA ETRE PRECEDEE :", QLineEdit::Normal,"valeur", &ok);
          try
          {
              if (ok && !id.isEmpty())
              {
                     TacheU* t = dynamic_cast<TacheU*>(TM.getTache(id));
                    this->liste_taches->setHtml(TM.afficherTachesAProgrammer()); //mise à jour du texte du dock widget des tâches à programmer
                    QString id2 = QInputDialog::getText(this,"Tache","Entrez l'id de la Tache Qui Precede :", QLineEdit::Normal,"valeur", &ok2);
                     TacheU* preced = dynamic_cast<TacheU*>(TM.getTache(id2));
                    if(ok2 && !id2.isEmpty())
                        TM.ajouterPrecedenceTache(t,preced);
                    QMessageBox msgBox;
                    msgBox.setText("Precedence Ajoutee!");
                    msgBox.exec();

              }

           }

          catch (CalendarException ce) {
                  QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);}

              catch (std::exception e) {
                     QMessageBox::information(0,"Erreur",e.what(),QMessageBox::Ok);}


 }

 void AgendaWindow::ajouter_tache_a_composite()
 {
     bool ok,ok2;
     QString id = QInputDialog::getText(this,"Tache","Entrez l'id de la Tache Composite :", QLineEdit::Normal,"valeur", &ok);
     QString id2 = QInputDialog::getText(this,"Tache","Entrez l'id de la Tache:", QLineEdit::Normal,"valeur", &ok2);
          try
          {
              if (ok && ok2 && !id.isEmpty() && !id2.isEmpty())
              {
                   TacheC* C = dynamic_cast<TacheC*>(TM.getTache(id));
                    //this->liste_taches->setHtml(TM.afficherTachesAProgrammer()); //mise à jour du texte du dock widget des tâches à programmer
                    Tache* comp=TM.getTache(id2);
                    TM.ajouter_Tache_a_composite(C,comp);
                    QMessageBox msgBox;
                    msgBox.setText("Tache Ajoutee a Composite!");
                    msgBox.exec();

              }

           }

          catch (CalendarException ce) {
                  QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);}

              catch (std::exception e) {
                     QMessageBox::information(0,"Erreur",e.what(),QMessageBox::Ok);}
 }

void AgendaWindow::ajouter_activite() {
    QString *type;
    QString *id;
    QString *title;
    Date *date;
    Horaire *time;
    Duree *duration;
    QString *place;
    QString *people;
    NewActivity *fenetre_activite = new NewActivity(this);
    Activite* activite;
    try {
        if(fenetre_activite->exec()) {
            id = new QString(fenetre_activite->getId().text());
            title = new QString(fenetre_activite->getTitle().text());
            duration = new Duree(fenetre_activite->getDuration().time().hour(),fenetre_activite->getDuration().time().minute());
            time = new Horaire(fenetre_activite->getTime().time().hour(),fenetre_activite->getTime().time().minute());
            date = new Date(fenetre_activite->getDate().date().day(),fenetre_activite->getDate().date().month(),fenetre_activite->getDate().date().year());
            type = new QString(fenetre_activite->getType().currentText());
            place = new QString(fenetre_activite->getPlace().text());
            people = new QString(fenetre_activite->getPeople().text());
            if(type == QString("RDV"))
                activite =  new Rdv(*id,*title,*duration,*place,*people);
            else
                activite =  new Reunion(*id,*title,*duration,*place);
            ProgM.ajouterProgrammation(activite, *date, *time);
            int temp = date->getAnnee();
            int *year = &temp;
            if((choix_semaine->value() == date->toQDate().weekNumber(year)) && (choix_annee->value() == date->getAnnee())) {
                placer_evenement(activite);
            }
        }
    } catch (CalendarException ce) {
        QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);
        }
      catch (std::exception e) {
        QMessageBox::information(0,"Erreur",e.what(),QMessageBox::Ok);
    }
}

 void AgendaWindow::supprimer_tache()
 {
     bool ok;
     QString message= "Id :  ";
     QString id = QInputDialog::getText(this,"Tache","Entrez l'id de la Tache à Supprimer :", QLineEdit::Normal,"valeur", &ok);
     try
     {
         if (ok && !id.isEmpty())
         {
             TM.remove_Task(id);
             QMessageBox msgBox;
             msgBox.setText("Tache Supprimée ");
             msgBox.exec();

             PM.remove_Task(id);
             QMessageBox msgBox2;
             msgBox2.setText("Tache Supprimée de Projet");
             msgBox2.exec();

             Programmation* p=ProgM.getProg(id);
             if(p->getEvent()->cestunetache())
             {
                ProgM.remove_programmation(id); // c'est une tache qu'on veut supprimer
                QMessageBox msgBox3;
                msgBox3.setText("Tache Supprimée de Programmation");
                 msgBox3.exec();
             }
             else
                 throw CalendarException("La Tache n'est pas Programée");



        }

     }
         catch (CalendarException ce) {
                 QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);}

             catch (std::exception e) {
                    QMessageBox::information(0,"Erreur",e.what(),QMessageBox::Ok);}

}


 void AgendaWindow::recherche_projet()
 {
     bool ok;
     QString message= "Id :  ";
     QString id = QInputDialog::getText(this,"Projet","Entrez l'id du Projet :", QLineEdit::Normal,"valeur", &ok);
     try
     {
         if (ok && !id.isEmpty())
         {
     message+=(id);
     Projet* p = PM.getProjet(id);
     message+="\n Titre : ";
     QString *titre = new QString(p->getTitre());
     message+=(*titre);
     message+="\n Diponiblite : ";
     QString dispo= QString::number(p->getDisponibilite().getAnnee());
     dispo+="/";dispo+= QString::number(p->getDisponibilite().getMois());
     dispo+="/";dispo+= QString::number(p->getDisponibilite().getJour());
     QString* disponibilite= new QString(dispo);
     message+=disponibilite;
     message+="\n Echeance : ";
     QString ech= QString::number(p->getEcheance().getAnnee());
     ech+="/";ech+= QString::number(p->getEcheance().getMois());
     ech+="/";ech+= QString::number(p->getEcheance().getJour());
     QString* echeance = new  QString(ech);
     message+=echeance;
     message+="\n Taches: ";

     for (std::vector<Tache*>::iterator itt = p->GetTabProjet().begin(); itt!=p->GetTabProjet().end(); ++itt)
     {
       message+= "  "+(*itt)->getId();
       message+= " : "+(*itt)->getTitre();
       message+="*****";
     }

    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
    }
     }
         catch (CalendarException ce) {
                 QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);}

             catch (std::exception e) {
                    QMessageBox::information(0,"Erreur",e.what(),QMessageBox::Ok);}

     }


 void AgendaWindow::recherche_tache()
 {
     bool ok;
      QString message= "Id : ";
     QString id = QInputDialog::getText(this,"Tache","Entrez l'id de la Tache Recherchee :", QLineEdit::Normal,"valeur", &ok);
     try
     {
         if (ok && !id.isEmpty())
         {
     Tache* t= TM.getTache(id);
     message+= id;
     QString* titre = new QString(t->getTitre());
     message+=("\n Titre : "); message+=(*titre);
     unsigned int H = t->getDuree().getHeure();
     unsigned int M = t->getDuree().getMinute();
     QString h = (H<10)?"0"+QString::number(H):""+QString::number(H);
     QString m = (M<10)?"0"+QString::number(M):""+QString::number(M);
     QString* duree = new QString(h+" H "+m);
     QString dispo= QString::number(t->getDisponibilite().getAnnee());
     dispo+="/";dispo+= QString::number(t->getDisponibilite().getMois());
     dispo+="/";dispo+= QString::number(t->getDisponibilite().getJour());
     QString* disponibilite= new QString(dispo);
     QString ech= QString::number(t->getEcheance().getAnnee());
     ech+="/";ech+= QString::number(t->getEcheance().getMois());
     ech+="/";ech+= QString::number(t->getEcheance().getJour());
     QString* echeance = new  QString(ech);
     message+="\n Duree : "; message+= duree ;
     message+="\n Diponibilite : "; message+=disponibilite;
     message+="\n Echeance : "; message+=echeance;
     message+="\n";
     if (t->getTypeTache()) //unitaire
     {
          QString* type = new QString("Unitaire");
          message+=("\n Type : ");message+=(*type);
          TacheU* tempTask = dynamic_cast<TacheU*>(t);

            if(tempTask->isPreemptive())
            {
                message+="\n Tache Preemptive";
                message+="\n Progression: ";
                message+=tempTask->getProgression();
            }
         else message+="\n Tache Non Preemptive";

         message+=("\n\n Taches Precedentes:");
         for ( std::vector<TacheU *>::iterator it = tempTask->getPrecedence().begin(); it != tempTask->getPrecedence().end(); ++it)
         {
             message+= "  "+(*it)->getId();
             message+= " : "+(*it)->getTitre();
             message+="*****";
         }
         message +="\n\n";
         message+=(" Taches Suivantes: ");
         for (std::vector<TacheU *>::iterator it = tempTask->getSuivante().begin(); it != tempTask->getSuivante().end(); ++it)
         {    message+= "  "+(*it)->getId();
             message+= " : "+(*it)->getTitre();
             message+="*****";
         }
     }
     else
     {
         TacheC* tempTask = dynamic_cast<TacheC*>(t);
         message+=(" Taches : ");
         for(std::vector<Tache *>::iterator it= tempTask->getCTaches().begin();it!= tempTask->getCTaches().end();it++)
            message += " "+(*it)->getId();
         message +="\n";
     }

     QMessageBox msgBox;
     msgBox.setText(message);
     msgBox.exec();
     }
   }
     catch (CalendarException ce) {
             QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);}

         catch (std::exception e) {
                QMessageBox::information(0,"Erreur",e.what(),QMessageBox::Ok);}

 }

 void AgendaWindow::recherche_programmation()
 {
     bool ok;
     QString message= "Id : ";
     const QString&  id = QInputDialog::getText(this,"Programmation","Entrez l'id de l'Evenement Recherche' :", QLineEdit::Normal,"valeur", &ok);
     try
     {
     if (ok && !id.isEmpty())
     {
        Programmation* ev=ProgM.getProg(id);
         message+=id;
         message+="\n Titre :";
         message+=ev->getEvent()->getTitre();
         message+="\n Date ";
     QString d= QString::number(ev->getDate().getAnnee());
     d+="/";d+= QString::number(ev->getDate().getMois());
     d+="/";d+= QString::number(ev->getDate().getJour());
     QString* date= new QString(d);
     message+=date;
     message+="\n Horaire ";
     unsigned int hh = ev->getHoraire().getHeure();
     unsigned int mm = ev->getHoraire().getMinute();
     QString h1 = (hh<10)?"0"+QString::number(hh):""+QString::number(hh);
     QString m1 = (mm<10)?"0"+QString::number(mm):""+QString::number(mm);
     QString* horaire = new QString(h1+" H "+m1);
     message+=horaire;
     ev->getHoraire().getHeure();
     message+="\n Duree: ";
     unsigned int H = ev->getEvent()->getDuree().getHeure();
     unsigned int M = ev->getEvent()->getDuree().getMinute();
     QString h = (H<10)?"0"+QString::number(H):""+QString::number(H);
     QString m = (M<10)?"0"+QString::number(M):""+QString::number(M);
     QString* duree = new QString(h+" H "+m);
     message+= duree;
     Event* temp = const_cast<Event*>(ev->getEvent());//!< On force la Conversion de l'objet Event en un Event non const pour pouvoir faire un dynamic cast ultérieurement
     if( ev->getEvent()->cestunetache())
     {

        TacheU* tempTask = dynamic_cast<TacheU*>(temp);//!< Pour passer d'une classe Mère à un classe fille on a besoin de faire une conversion explicite
        message+="\n Type: Tache Unitaire";
        if(tempTask->isPreemptive())
        {
            message+="\n Tache Preemptive";
            message+="\n Progression: ";
            QString p = QString::number(tempTask->getProgression());
            message+=p;
            message+="%";
        }
                else message+="\n Tache Non Preemptive";

     }
     else
     {

         Activite* tempActiv = dynamic_cast<Activite*>(temp);//!< Pour passer d'une classe Mère à un classe fille on a besoin de faire une conversion explicite
         message+="\n Type: Activite";
         message+="\n Lieu : ";
         message+=tempActiv->getLieu();
     }

     QMessageBox msgBox;
     msgBox.setText(message);
     msgBox.exec();
     }
 }

     catch (CalendarException ce) {
             QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);}

         catch (std::exception e) {
                QMessageBox::information(0,"Erreur",e.what(),QMessageBox::Ok);}

 }
void AgendaWindow::supprimer_projet()
{
    bool ok;
    QString message= "Id : ";
    const QString&  id = QInputDialog::getText(this,"Projet","Entrez l'id du Projet à supprimer :", QLineEdit::Normal,"valeur", &ok);
    try
    {
     if (ok && !id.isEmpty())
        {
         PM.removeProject(id);
         QMessageBox msgBox;
         msgBox.setText("Projet Supprimé!");
         msgBox.exec();

        }

    }

    catch (CalendarException ce) {
            QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);}

        catch (std::exception e) {
               QMessageBox::information(0,"Erreur",e.what(),QMessageBox::Ok);}

}

void AgendaWindow::supprimer_activite()
{
    bool ok;
    QString message= "Id : ";
    const QString&  id = QInputDialog::getText(this,"Programmation","Entrez l'id de l'Evenement Recherche' :", QLineEdit::Normal,"valeur", &ok);
    try
    {
        if (ok && !id.isEmpty())
        {
           Programmation* p=ProgM.getProg(id);
           if(!(p->getEvent()->cestunetache()))
           {
                   ProgM.remove_programmation(id);
                   QMessageBox msgBox;
                   msgBox.setText("Programmation Activité supprimée!");
                   msgBox.exec();

            }
        }
      else
       throw CalendarException("Cette Activité n'existe pas ou n'est pas Programmee");
    }


        catch (CalendarException ce) {
                QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);}

            catch (std::exception e) {
                   QMessageBox::information(0,"Erreur",e.what(),QMessageBox::Ok);}
}


void AgendaWindow::afficher_projets()
 {


     QStandardItemModel* model = new QStandardItemModel;
     QStandardItem *parentItem= model->invisibleRootItem();
     for (std::vector<Projet*>::const_iterator it =PM.getInstance().getTab().begin()  ; it!= PM.getInstance().getTab().end() ;it++ )
    {
         QString message;
         message=(*it)->getId();
         message+=" : ";
         message+=(*it)->getTitre();
         // I display a project

      QStandardItem* item=new QStandardItem(QString(message));
      item->setEditable(false);
      parentItem->appendRow(item);
      Projet* p = (*it);
      // I display every project's tasks

              for (std::vector<Tache*>::const_iterator itp = p->GetTabProjet().begin(); itp != p->GetTabProjet().end() ;itp++)
              {
                  QString message2;
                  message2=(*itp)->getId();
                  message2+=" : ";
                  message2+=(*itp)->getTitre();
                  QStandardItem* itemp = new QStandardItem(message2);
                  itemp->setEditable(false);
                  item->appendRow(itemp);

              }
     }

     QTreeView *treeView=new QTreeView;
     treeView->setModel(model);
     treeView->show();


 }

void afficher_proprietes(Activite *a) {
    QMessageBox message;
    message.setText("Propriétés de l'evenement");
    message.setInformativeText(a->toString());
    message.exec();
}

void afficher_proprietes(Tache* t) {
    QMessageBox message;
    message.setText("Propriétés de l'evenement");
    message.setInformativeText(t->toString());
    message.exec();
}


void AgendaWindow::afficher_taches()
{
    QStandardItemModel* model = new QStandardItemModel;
    QStandardItem *parentItem= model->invisibleRootItem();
    for (std::vector<Tache*>::const_iterator it =TM.getInstance().getTabTaches().begin()  ; it!= TM.getInstance().getTabTaches().end() ;it++ )
   {
        // I display a Task
    QString message=" ";
    message=(*it)->getId();
    message+=" : ";
    message+=(*it)->getTitre();
     QStandardItem* item=new QStandardItem(QString(message));
     item->setEditable(false);
     parentItem->appendRow(item);
     if(!(*it)->getTypeTache())
     {
         TacheC* p=dynamic_cast<TacheC*>(*it);

     // I display every composite task's tasks

             for (std::vector<Tache*>::const_iterator itp = p->getCTaches().begin(); itp != p->getCTaches().end() ;itp++)
             {
                 QString message2;
                 message2=(*itp)->getId();
                 message2+=" : ";
                 message2+=(*itp)->getTitre();

                 QStandardItem* itemp = new QStandardItem(message2);
                 itemp->setEditable(false);
                 item->appendRow(itemp);

             }
    }
    }

    QTreeView *treeView=new QTreeView;
    treeView->setModel(model);
    treeView->show();


}
void AgendaWindow::afficher_schedule()
{
    QStandardItemModel* model = new QStandardItemModel;
    QStandardItem *parentItem= model->invisibleRootItem();
    for (std::vector<Programmation*>::const_iterator it =ProgM.getInstance().getTabprogs().begin()  ; it!= ProgM.getInstance().getTabprogs().end() ;it++ )
   {
        QString message=" ";
        message=(*it)->getEvent()->getId();
        message+=" : ";
        message+=(*it)->getEvent()->getTitre();
        message+="\n             ";
        QString date= QString::number((*it)->getDate().getAnnee());
        date+="/";date+= QString::number((*it)->getDate().getMois());
        date+="/";date+= QString::number((*it)->getDate().getJour());
        QString* voila = new  QString(date);
        message+="Date :";message+=voila;
        unsigned int hh = ((*it)->getHoraire().getHeure());
        unsigned int mm = ((*it)->getHoraire().getMinute());
        QString h1 = (hh<10)?"0"+QString::number(hh):""+QString::number(hh);
        QString m1 = (mm<10)?"0"+QString::number(mm):""+QString::number(mm);
        QString* horaire = new QString(h1+" H "+m1);
        message+="  --Horaire : "; message+=horaire;
        if((*it)->getEvent()->cestunetache())
        {
            Event* temp=const_cast<Event*>((*it)->getEvent());
            TacheU* t=dynamic_cast<TacheU*>(temp);
            if(t->isPreemptive())
            {
                unsigned int completed=(t->getDuree().getDureeEnMinutes())*(t->getProgression())/100;
                unsigned int ce_qui_reste =t->getDuree().getDureeEnMinutes()-completed;
                Duree d(ce_qui_reste);
                message+="\n              preemtive:  Il reste :";
                if(ce_qui_reste>60)
                {
                    double d2= d.getDureeEnHeures();
                    message+= QString::number(d2);
                    message+=" H à programmer \n";
                }
                else
                {
                    message+= QString::number(ce_qui_reste);
                    message+="  minutes à programmer \n";
                }

            }


      }

         QStandardItem* item=new QStandardItem(QString(message));
         parentItem->appendRow(item);

    }
    QTreeView *treeView=new QTreeView;
    treeView->setModel(model);
    treeView->show();

}


 //******************************************************************************************


QRectF ItemActivite::boundingRect() const {
    int minutes = a->getDuree().getDureeEnMinutes();
    qreal hauteur = minutes *25/60;
    return QRectF(0,0,100,hauteur);
}

void ItemActivite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);
    painter->fillRect(rec,brush);
    painter->drawRect(rec);
    painter->drawText(rec, Qt::AlignCenter, a->getTitre()+" "+a->getId());
}

//******************************************************************************************

QRectF ItemTache::boundingRect() const {
    int minutes = t->getDuree().getDureeEnMinutes();
    qreal hauteur = minutes *25/60;
    return QRectF(0,0,100,hauteur);
}

void ItemTache::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QRectF rec = boundingRect();
    QBrush brush(Qt::red);
    painter->fillRect(rec,brush);
    painter->drawRect(rec);
    painter->drawText(rec, Qt::AlignCenter, t->getTitre()+" "+t->getId());
}


//******************************************************************************************



ActiviteInfo::ActiviteInfo(Activite *a, QWidget *parent, Qt::WindowFlags f) {
    this->setWindowTitle("Activite "+a->getId());
    id = new QLabel(a->getId(), this);
    titre = new QLabel(a->getTitre(), this);
    duree = new QLabel(a->getDuree().toString(), this);
    lieu = new QLabel(a->getLieu(), this);
    formLayout = new QFormLayout(this);

    formLayout->addRow("id : ", id);
    formLayout->addRow("titre : ", titre);
    formLayout->addRow("duree : ", duree);
    formLayout->addRow("Lieu : ", this);

    setLayout(formLayout);
}

