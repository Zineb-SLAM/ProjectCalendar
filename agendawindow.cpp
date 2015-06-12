#include "agendawindow.h"
#include "window.h"

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
    scene = new CustomQGraphicsScene(this);
    visu = new QGraphicsView(scene, this);
    visu->setFixedSize(700,600);
    emploi_du_temps->addItem(jours);
    emploi_du_temps->addWidget(visu);

    //couche semaine
    spacer_semaine = new QSpacerItem(50,0,QSizePolicy::Expanding,QSizePolicy::Preferred);
    s = new QLabel("Semaine", this);
    choix_semaine = new QSpinBox(this);
    semaine->addItem(spacer_semaine);
    semaine->addWidget(s);
    semaine->addWidget(choix_semaine);

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
}

//fonctions des slots

void AgendaWindow::changer_semaine(const unsigned int& s) {

}

/*void AgendaWindow::placer_tache(Tache* t) {
    ItemTache *tache = new ItemTache(t);
    scene->addItem(tache);
    tache->setFocus();
}*/

void AgendaWindow::placer_evenement(Activite* a) {
    ItemActivite *activite = new ItemActivite(a);
    scene->addItem(activite);
    activite->setFocus();
}

void AgendaWindow::placer_evenement(TacheU *t) {
    ItemTache *tache = new ItemTache(t);
    scene->addItem(tache);
    tache->setFocus();
}

void AgendaWindow::deplacer_tache(const Tache *t) {

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
            placer_evenement(t);
        }
    } catch (CalendarException ce) {
        QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);
      }
    catch (std::exception e) { QMessageBox::information(0,"Erreur",e.what(),QMessageBox::Ok);}
}

void AgendaWindow::ajouter_projet() {
    NewProject *fenetre_projet = new NewProject(this);
    for(std::vector<Tache *>::iterator it = TM.getTabTaches().begin(); it != TM.getTabTaches().end(); it++) {
        new QListWidgetItem((*it)->getTitre(), fenetre_projet->getTasks());
    }

    fenetre_projet->exec();
}

void AgendaWindow::ajouter_tache() {
    QString *id;
    QString *title;
    Duree *duration;
    Date *dispo;
    Date *deadl;
    QString *t;
    NewTask *fenetre_tache = new NewTask(this);
    Tache* tache;
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
            tache = &(TM.ajouterTacheU(*id,*title,*duration,*dispo,*deadl));
        else
            tache = &(TM.ajouterTacheC(*id,*title,*duration,*dispo,*deadl));
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
        placer_evenement(activite);
    } catch (CalendarException ce) {
        QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok);
        }
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
    return QRectF(-15,-7,30,14);
}

void ItemActivite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawRoundedRect(-15,-7,30,14,5,5);
    painter->drawText(boundingRect(), Qt::AlignCenter, a->getTitre());
}

void ItemActivite::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left) {
        afficher_proprietes(this->a);
    }
}

QRectF ItemTache::boundingRect() const {
    return QRectF(-15,-7,30,14);
}

void ItemTache::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawRoundedRect(-15,-7,30,14,5,5);
    painter->drawText(boundingRect(), Qt::AlignCenter, t->getTitre());
}

void ItemTache::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left) {
        afficher_proprietes(this->t);
    }
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
