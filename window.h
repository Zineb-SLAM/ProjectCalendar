#ifndef WINDOW_H
#define WINDOW_H

#include <math.h>
#include <QtWidgets>

#include"calendar.h"
#include"timing.h"
#include"programmation.h"
#include"projet.h"
#include"tache.h"
#include"evenement.h"


class NewProject: public QDialog {
    Q_OBJECT
    QDialogButtonBox* buttonBox;
    QLineEdit* identifier;
    QLineEdit* title;
    QTimeEdit* duration;
    QDateEdit* disponibility;
    QDateEdit* deadline;
    QListView* tasks;

    QFormLayout* formLayout;

public:
    NewProject(QWidget* parent = 0);
public slots:
    //void addNewProject();


};

class NewTask : public QDialog {
    Q_OBJECT
    QDialogButtonBox* buttonBox;

    QLineEdit* id;
    QLineEdit* title;
    QTimeEdit *duration;
    QDateEdit* disponibility;
    QDateEdit* deadline;
    QComboBox* taskType;
    QListView* predecessors;

    QFormLayout* formLayout;

public:
    NewTask(QWidget* parent = 0);
public slots:
    //void addNewTask();
};

class NewActivity : public QDialog {
    Q_OBJECT
    QDialogButtonBox* buttonBox;
    QComboBox* type;// RDV or Meeting
    QLineEdit* id;
    QLineEdit* title;
    QDateEdit* date;
    QTimeEdit* time;
    QTimeEdit *duration;
    QLineEdit* place;
    QLineEdit* people;

    QFormLayout* formLayout;

public:
   NewActivity(QWidget* parent);

public slots:
    //void addNewActivity();
};

class NewProgrammation : public QDialog {
    Q_OBJECT
    QDialogButtonBox* buttonBox;

    QListView* events;// RDV or Meeting
    QTimeEdit *schedule;
    QDateEdit* date;

    QFormLayout* formLayout;

public:
    NewProgrammation(QWidget* parent);
    const QTimeEdit& getSchedule() const { return *schedule; }
    const QDateEdit& getDate() const { return *date; }

public slots:
    //void addProgrammation();
};

class MainWindow:public QWidget
{
    QTreeView projectsview;
};

#endif // WINDOW_H
