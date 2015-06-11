#include "window.h"

NewProject::NewProject(QWidget *parent) {
    buttonBox = new QDialogButtonBox(this);
    identifier = new QLineEdit(this);
    title = new QLineEdit(this);
    duration = new QTimeEdit(this);
    disponibility = new QDateEdit(this);
    deadline = new QDateEdit(this);
    tasks = new QListView(this);

    formLayout = new QFormLayout(this);
    formLayout->addRow("Id", identifier);
    formLayout->addRow("Titre", title);
    formLayout->addRow("Duree", duration);
    formLayout->addRow("Disponibilite", disponibility);
    formLayout->addRow("Echeance", deadline);
    formLayout->addRow("Taches", tasks);
    setLayout(formLayout);
}

NewTask::NewTask(QWidget* parent) {
    buttonBox = new QDialogButtonBox(this);
    id = new QLineEdit(this);
    title = new QLineEdit(this);
    duration = new QTimeEdit(this);
    disponibility = new QDateEdit(this);
    deadline = new QDateEdit(this);
    taskType = new QComboBox(this);
    predecessors = new QListView(this);

    formLayout = new QFormLayout(this);
    formLayout->addRow("Id", id);
    formLayout->addRow("Titre", title);
    formLayout->addRow("Duree", duration);
    formLayout->addRow("Disponibilite", disponibility);
    formLayout->addRow("Echeance", deadline);
    formLayout->addRow("Type de la tache", taskType);
    formLayout->addRow("Predecesseurs", predecessors);
    setLayout(formLayout);
}

NewActivity::NewActivity(QWidget* parent) {
    buttonBox = new QDialogButtonBox(this);
    type = new QComboBox(this);
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
    setLayout(formLayout);
}

NewProgrammation::NewProgrammation(QWidget* parent) {
    buttonBox = new QDialogButtonBox(this);
    events = new QListView(this);
    schedule = new QTimeEdit(this);
    date = new QDateEdit(this);

    formLayout = new QFormLayout(this);
    formLayout->addRow("Evenements", events);
    formLayout->addRow("Date", date);
    formLayout->addRow("Horaire", schedule);
    setLayout(formLayout);
}
