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
    h = new QLabel("Horaire",this);
    label_00h = new QLabel("00h", this);
    label_01h = new QLabel("01h", this);
    label_02h = new QLabel("02h", this);
    label_03h = new QLabel("03h", this);
    label_05h = new QLabel("04h", this);
    label_04h = new QLabel("05h", this);
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
    heures->addWidget(h);
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
    scene->setSceneRect(-350,-300,700,600);
    visu = new QGraphicsView(scene);
    //visu->setFixedSize(700,600);
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
    liste_projets->textCursor().insertText(PM.afficherTitreProjets());
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

}

void AgendaWindow::createActions() {
    charger = new QAction("Charger",this);
    connect(charger, SIGNAL(triggered()), this, SLOT(charger_agenda()));

    exporter = new QAction("Exporter",this);
    connect(exporter, SIGNAL(triggered()), this, SLOT(sauvegarder_agenda()));

    programmer_tache = new QAction("Programmer",this);
    connect(programmer_tache, SIGNAL(triggered()), this, SLOT(demander_programmer()));

    creer_projet = new QAction("Creer un projet", this);
    connect(creer_projet, SIGNAL(triggered()), this, SLOT(ajouter_projet()));

    creer_tache = new QAction("Creer une tache", this);
    connect(creer_tache, SIGNAL(triggered()), this, SLOT(ajouter_tache()));

    tout_afficher = new QAction("Afficher toutes les taches", this);
    connect(tout_afficher, SIGNAL(triggered()), this, SLOT(afficher()));

    creer_activite = new QAction("Creer une activite", this);
    connect(creer_activite, SIGNAL(triggered()), this, SLOT(ajouter_activite()));


    Rechercher_Projet=new QAction("Rechercher Un Projet", this);
    connect(Rechercher_Projet, SIGNAL(triggered()), this, SLOT(recherche_projet()));

    Rechercher_Tache=new QAction("Rechercher Une Tache", this);
    connect(Rechercher_Tache, SIGNAL(triggered()), this, SLOT(recherche_tache()));

    Rechercher_Programmation=new QAction("Rechercher Un Evenement", this);
    connect(Rechercher_Programmation, SIGNAL(triggered()), this, SLOT(recherche_programmation()));


}

void AgendaWindow::createMenus() {
    menu_options = menuBar()->addMenu("Options");
    menu_options->addAction(charger);
    menu_options->addAction(exporter);
    menu_options->addAction(tout_afficher);

    menu_tache = menuBar()->addMenu("Tache");
    menu_tache->addAction(creer_tache);
    menu_tache->addAction(programmer_tache);

    menu_projet = menuBar()->addMenu("Projet");
    menu_projet->addAction(creer_projet);

    menu_activite = menuBar()->addMenu("Activite");
    menu_activite->addAction(creer_activite);

    menu_activite = menuBar()->addMenu("Rechercher");
    menu_activite->addAction(Rechercher_Projet);
    menu_activite->addAction(Rechercher_Tache);
     menu_activite->addAction(Rechercher_Programmation);
}

//fonctions des slots

void AgendaWindow::changer_semaine() {
    scene->clear();
    scene->update();
    int s = choix_semaine->value();
    int a = choix_annee->value();
    for(std::vector<Programmation *>::iterator it = ProgM.getTabprogs().begin(); it != ProgM.getTabprogs().end(); it++) {
        //if((choix_semaine->value() == date->toQDate().weekNumber(year)) && (choix_annee->value() == date->getAnnee()))
        int temp = (*it)->getDate().getAnnee();
        int *year = &temp;
        if((s == (*it)->getDate().toQDate().weekNumber(&temp)) && (a == (*it)->getDate().getAnnee()))
            if(!((*it)->getEvent()->cestunetache())) {
                Event *temp = const_cast<Event *>((*it)->getEvent());
                placer_evenement(dynamic_cast<Activite *>(temp));
            }
            else {
                Event *temp = const_cast<Event *>((*it)->getEvent());
                placer_evenement(dynamic_cast<TacheU *>(temp));
            }
    }
}

void AgendaWindow::placer_evenement(Activite* a) {
    ItemActivite *activite = new ItemActivite(a);
    QDate date_prog = ProgM.getProg(a->getId())->getDate().toQDate();
    int jour = date_prog.dayOfWeek() - 1; //lundi : 0, mardi : 1...
    qreal x = jour * 100;
    unsigned int debutH = ProgM.trouverProgrammation(a)->getHoraire().getHeure();
    unsigned int debutM = ProgM.trouverProgrammation(a)->getHoraire().getMinute();
    int nbMinutes = (60 * debutH) + debutM;
    qreal y = (nbMinutes * 25) / 60;
    scene->addItem(activite);
    activite->setPos(scene->sceneRect().left()+x,scene->sceneRect().top()+y);
}

void AgendaWindow::placer_evenement(TacheU *t) {
    ItemTache *tache = new ItemTache(t);
    QDate date_prog = ProgM.getProg(t->getId())->getDate().toQDate();
    int jour = date_prog.dayOfWeek() - 1; //lundi : 0, mardi : 1...
    qreal x = jour * 100;
    unsigned int debutH = ProgM.trouverProgrammation(t)->getHoraire().getHeure();
    unsigned int debutM = ProgM.trouverProgrammation(t)->getHoraire().getMinute();
    qreal y = (60 * debutH) + debutM;
    scene->addItem(tache);
    tache->setPos(scene->sceneRect().left()+x,scene->sceneRect().top()+y);
}

void AgendaWindow::charger_agenda() {
    QString chemin = QFileDialog::getOpenFileName();
    PM.load(chemin);
}

void AgendaWindow::sauvegarder_agenda() {
    QString chemin = QFileDialog::getSaveFileName();
    PM.save(chemin);
}

void AgendaWindow::demander_programmer() {
    bool ok;
    Horaire *h;
    Date *d;
    QString id = QInputDialog::getText(this,"Programmer","Entrez l'id de la tache à programmer :", QLineEdit::Normal,"valeur", &ok);
    try {
        if (ok && !id.isEmpty()) {
            TacheU* t = dynamic_cast<TacheU*>(TM.getTache(id));
            NewProgrammation *fenetre_programmation = new NewProgrammation(this);
            if(fenetre_programmation->exec()) {
                h = new Horaire(fenetre_programmation->getSchedule().time().hour(), fenetre_programmation->getSchedule().time().minute());
                d = new Date(fenetre_programmation->getDate().date().day(),fenetre_programmation->getDate().date().month(),fenetre_programmation->getDate().date().year());
            }
            ProgM.ajouterProgrammation(t,*d,*h);
            int temp = d->getAnnee();
            int *year = &temp;
            if((choix_semaine->value() == d->toQDate().weekNumber(year)) && (choix_annee->value() == d->getAnnee())) {
                QMessageBox::information(0,"coucou","même semaine et annee",QMessageBox::Ok);
                placer_evenement(t);
            }
        }
    } catch (CalendarException ce) {
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
    if(fenetre_projet->exec()) {
        id = new QString(fenetre_projet->getId().text());
        title = new QString(fenetre_projet->getTitle().text());
        disponibility = new Date(fenetre_projet->getDisponibility().date().day(), fenetre_projet->getDisponibility().date().month(), fenetre_projet->getDisponibility().date().year());
        deadline = new Date(fenetre_projet->getDeadline().date().day(), fenetre_projet->getDeadline().date().month(), fenetre_projet->getDeadline().date().year());
    }
    try {
        PM.creerProjet(*id,*title,*disponibility,*deadline);
    } catch (CalendarException ce) {
        QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);
        }
    this->liste_projets->setHtml(PM.afficherTitreProjets()); //mise à jour du texte du dock widget des tâches à programmer

}

void AgendaWindow::ajouter_tache() {
    QString *id;
    QString *title;
    Duree *duration;
    Date *dispo;
    Date *deadl;
    QString *t;
    NewTask *fenetre_tache = new NewTask(this);
    try {
        if(fenetre_tache->exec()) {
            id = new QString(fenetre_tache->getId().text());
            title = new QString(fenetre_tache->getTitle().text());
            //h = new Horaire(fenetre_programmation->getSchedule().time().hour(), fenetre_programmation->getSchedule().time().minute());
            //d = new Date(fenetre_programmation->getDate().date().day(),fenetre_programmation->getDate().date().month(),fenetre_programmation->getDate().date().year());
            duration = new Duree(fenetre_tache->getDuration().time().hour(),fenetre_tache->getDuration().time().minute());
            dispo = new Date(fenetre_tache->getDisponibility().date().day(),fenetre_tache->getDisponibility().date().month(),fenetre_tache->getDisponibility().date().year());
            deadl = new Date(fenetre_tache->getDeadline().date().day(),fenetre_tache->getDeadline().date().month(),fenetre_tache->getDeadline().date().year());
            t = new QString(fenetre_tache->getType().currentText());
        }
        if(t == QString("unitaire"))
            TM.ajouterTacheU(*id,*title,*duration,*dispo,*deadl);
        else
            TM.ajouterTacheC(*id,*title,*duration,*dispo,*deadl);
        this->liste_taches->setHtml(TM.afficherTachesAProgrammer()); //mise à jour du texte du dock widget des tâches à programmer
    } catch (CalendarException ce) {
        QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);
        }
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
        }
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
        else
            QMessageBox::information(0,"erreur",QString::number(date->toQDate().weekNumber(year)),QMessageBox::Ok);

    } catch (CalendarException ce) {
        QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);
        }
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
         {    message+= "  "+(*it)->getId();
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


void AgendaWindow::afficher() {
    //insérer toutes les taches existantes dans l'agenda
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
    painter->drawText(rec, Qt::AlignCenter, a->getTitre());
}

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
    painter->drawText(rec, Qt::AlignCenter, t->getTitre());
}

void AgendaWindow::TreeViewProjet()
{
    QStandardItem* parent = projectsTreeV->invisibleRootItem();

    for (std::vector<Projet*>::const_iterator it =PM.getInstance().getTab().begin() ; it!= PM.getInstance().getTab().end() ;it++ )
    {
        QStandardItem* item = new QStandardItem((*it)->getId());
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        parent->appendRow(item);

        Projet* p = (*it);

        for (std::vector<Tache*>::const_iterator itp = p->GetTabProjet().begin(); itp != p->GetTabProjet().end() ;itp++)
        {
            QStandardItem* itemp = new QStandardItem((*itp)->getId());
            itemp->setFlags(itemp->flags() & ~Qt::ItemIsEditable);
            itemp->appendRow(itemp);


        }
    }
}
