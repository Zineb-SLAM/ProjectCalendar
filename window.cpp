#include "window.h"

NewProject::NewProject(QWidget *parent) {
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    identifier = new QLineEdit(this);
    title = new QLineEdit(this);
    duration = new QTimeEdit(this);
    disponibility = new QDateEdit(this);
    deadline = new QDateEdit(this);
    tasks = new QListWidget(this);

    formLayout = new QFormLayout(this);
    formLayout->addRow("Id", identifier);
    formLayout->addRow("Titre", title);
    formLayout->addRow("Duree", duration);
    formLayout->addRow("Disponibilite", disponibility);
    formLayout->addRow("Echeance", deadline);
    formLayout->addRow("Taches", tasks);
    formLayout->addWidget(buttonBox);
    setLayout(formLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

NewTask::NewTask(QWidget* parent) {
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    id = new QLineEdit(this);
    title = new QLineEdit(this);
    duration = new QTimeEdit(this);
    disponibility = new QDateEdit(this);
    deadline = new QDateEdit(this);
    taskType = new QComboBox(this);
    taskType->addItem("unitaire");
    taskType->addItem("composite");
    predecessors = new QListWidget(this);

    formLayout = new QFormLayout(this);
    formLayout->addRow("Id", id);
    formLayout->addRow("Titre", title);
    formLayout->addRow("Duree", duration);
    formLayout->addRow("Disponibilite", disponibility);
    formLayout->addRow("Echeance", deadline);
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
    time = new QTimeEdit(this);
    duration = new QTimeEdit(this);

    formLayout = new QFormLayout(this);
    formLayout->addRow("Type", type);
    formLayout->addRow("Id", id);
    formLayout->addRow("Titre", title);
    formLayout->addRow("Date", date);
    formLayout->addRow("Horaire", time);
    formLayout->addRow("Duree", duration);
    formLayout->addWidget(buttonBox);
    setLayout(formLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

NewProgrammation::NewProgrammation(QWidget* parent) {
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    events = new QListWidget(this);
    schedule = new QTimeEdit(this);
    date = new QDateEdit(this);

    formLayout = new QFormLayout(this);
    formLayout->addRow("Evenements", events);
    formLayout->addRow("Date", date);
    formLayout->addRow("Horaire", schedule);
    formLayout->addWidget(buttonBox);
    setLayout(formLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}
