#include "window.h"
#include "tache.h"

NewProject::NewProject(QWidget *parent) {
    TacheManager& TM = TacheManager::getInstance();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    identifier = new QLineEdit(this);
    title = new QLineEdit(this);
    disponibility = new QDateEdit(this);
    disponibility->setMinimumDate(QDate(QDate::currentDate())); //on ne peut pas créer un projet dans le passé
    deadline = new QDateEdit(this);
    deadline->setMinimumDate(QDate(QDate::currentDate()));
    tasks = new QListWidget(this);

    for(TacheManager::tabtaches::iterator it = TM.getTabTaches().begin(); it != TM.getTabTaches().end(); it++) {
        new QListWidgetItem((*it)->getTitre(), getTasks());
    }

    formLayout = new QFormLayout(this);
    formLayout->addRow("Id", identifier);
    formLayout->addRow("Titre", title);
    formLayout->addRow("Disponibilite", disponibility);
    formLayout->addRow("Echeance", deadline);
    formLayout->addRow("Taches", tasks);
    formLayout->addWidget(buttonBox);
    setLayout(formLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

NewTask::NewTask(QWidget* parent) {
    TacheManager& TM = TacheManager::getInstance();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    id = new QLineEdit(this);
    title = new QLineEdit(this);
    duration = new QTimeEdit(this);
    disponibility = new QDateEdit(this);
    disponibility->setMinimumDate(QDate(QDate::currentDate()));
    deadline = new QDateEdit(this);
    deadline->setMinimumDate(QDate(QDate::currentDate()));
    taskType = new QComboBox(this);
    taskType->addItem("unitaire");
    taskType->addItem("composite");
    predecessors = new QListWidget(this);
    preemtive = new QCheckBox("Preemptive", this);
    for(vector<Tache *>::iterator it = TM.getTabTaches().begin(); it != TM.getTabTaches().end(); it++)
    {
        new QListWidgetItem((*it)->getTitre(), predecessors);
    }

    formLayout = new QFormLayout(this);
    formLayout->addRow("Id", id);
    formLayout->addRow("Titre", title);
    formLayout->addRow("Duree", duration);
    formLayout->addRow("Disponibilite", disponibility);
    formLayout->addRow("Echeance", deadline);
    formLayout->addWidget(preemtive);
    formLayout->addRow("Type de la tache", taskType);
    formLayout->addRow("Predecesseurs", predecessors);
    formLayout->addWidget(buttonBox);

    setLayout(formLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

NewActivity::NewActivity(QWidget* parent) {
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    type = new QComboBox(this);
    type->addItem("RDV");
    type->addItem("réunion");
    id = new QLineEdit(this);
    title = new QLineEdit(this);
    date = new QDateEdit(this);
    date->setMinimumDate(QDate(QDate::currentDate()));
    time = new QTimeEdit(this);
    duration = new QTimeEdit(this);
    place = new QLineEdit(this);
    people = new QLineEdit(this);

    formLayout = new QFormLayout(this);
    formLayout->addRow("Type", type);
    formLayout->addRow("Id", id);
    formLayout->addRow("Titre", title);
    formLayout->addRow("Date", date);
    formLayout->addRow("Horaire", time);
    formLayout->addRow("Duree", duration);
    formLayout->addRow("Lieu", place);
    formLayout->addRow("Personne", people);
    formLayout->addWidget(buttonBox);
    setLayout(formLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

NewProgrammation::NewProgrammation(QWidget* parent) {
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    schedule = new QTimeEdit(this);
    date = new QDateEdit(this);
    date->setMinimumDate(QDate(QDate::currentDate()));

    formLayout = new QFormLayout(this);
    formLayout->addRow("Date", date);
    formLayout->addRow("Horaire", schedule);
    formLayout->addWidget(buttonBox);
    setLayout(formLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}
