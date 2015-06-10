#include "agendawindow.h"
#include "projet.h"

AgendaWindow::AgendaWindow()
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
    cadre = new QGraphicsView(this);
    emploi_du_temps->addItem(jours);
    emploi_du_temps->addWidget(cadre);

    //couche semaine
    spacer_semaine = new QSpacerItem(50,0,QSizePolicy::Expanding,QSizePolicy::Preferred);
    s = new QLabel("Semaine", this);
    choix_semaine = new QSpinBox(this);
    semaine->addItem(spacer_semaine);
    semaine->addWidget(s);
    semaine->addWidget(choix_semaine);

    //couche agenda
    spacer = new QSpacerItem(20,0,QSizePolicy::Preferred,QSizePolicy::Preferred);
    agenda->addItem(heures);
    agenda->addItem(spacer);
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
    liste_projets->setReadOnly(1); //en lecture seulement
    addDockWidget(Qt::LeftDockWidgetArea,projets);
    projets->setWidget(liste_projets);

    createActions();
    createMenus();

    //options = new QMenu;
    //barre_menu->addMenu(options);

    //vertical->addWidget(barre_menu);
    //vertical->addItem(agenda);

    /*idLineEdit->setText(t.getId());
    titreTextEdit->setText(t.getTitre());
    dateDispo->setDate(t.getDateDisponibilite());
    dateEcheance->setDate(t.getDateEcheance());
    dureeH->setValue(t.getDuree().getHeure());
    dureeM->setValue(t.getDuree().getMinute());
    save->setEnabled(false);
    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(sauverTache()));
    QObject::connect(idLineEdit,SIGNAL(textChanged(QString)),this,SLOT(activerButton()));
    QObject::connect(titreTextEdit,SIGNAL(textChanged(QString)),this,SLOT(activerButton()));
    QObject::connect(dateDispo, SIGNAL(dateChanged(QDate)),this,SLOT(activerButton()));
    QObject::connect(dateEcheance, SIGNAL(dateChanged(QDate)),this,SLOT(activerButton()));
    QObject::connect(dateEcheance, SIGNAL(dateChanged(QDate)),this,SLOT(verifierDate(const QDate&)));
    QObject::connect(dateDispo, SIGNAL(dateChanged(QDate)),this,SLOT(verifierDate(const QDate&)));
    QObject::connect(dureeH, SIGNAL(valueChanged(int)),this,SLOT(activerButton()));
    QObject::connect(dureeM, SIGNAL(valueChanged(int)),this,SLOT(activerButton()));
    QObject::connect(preemptive, SIGNAL(stateChanged(int)),this,SLOT(activerButton()));
    */
}

void AgendaWindow::createActions() {
    charger = new QAction("Charger",this);
    connect(charger, SIGNAL(triggered()), this, SLOT(charger_agenda()));

    exporter = new QAction("Exporter",this);
    connect(exporter, SIGNAL(triggered()), this, SLOT(sauvegarder_agenda()));

    programmer_tache = new QAction("Programmer",this);
    connect(programmer_tache, SIGNAL(triggered()), this, SLOT(programmer()));

    creer_projet = new QAction("Creer un projet", this);
    connect(creer_projet, SIGNAL(triggered()), this, SLOT(ajouter_projet()));
}

void AgendaWindow::createMenus() {
    menu_options = menuBar()->addMenu("Options");
    menu_options->addAction(charger);
    menu_options->addAction(exporter);

    menu_tache = menuBar()->addMenu("Tache");
    menu_tache->addAction(programmer_tache);

    menu_projet = menuBar()->addMenu("Projet");
    menu_projet->addAction(creer_projet);
}

//fonctions des slots

void AgendaWindow::changer_semaine(const unsigned int& s) {

}

void AgendaWindow::placer_tache(const Tache& t) {

}

void AgendaWindow::deplacer_tache(const Tache& t) {

}

void AgendaWindow::charger_agenda() {

}

void AgendaWindow::sauvegarder_agenda() {

}

void AgendaWindow::programmer() {

}

void AgendaWindow::ajouter_projet() {

}
