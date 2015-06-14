#ifndef WINDOW_H
#define WINDOW_H

#include <math.h>
#include <QtWidgets>

#include "calendar.h"
#include "timing.h"
#include "programmation.h"
#include "projet.h"
#include "evenement.h"


class NewProject: public QDialog {
    Q_OBJECT
    QDialogButtonBox* buttonBox;
    //QPushButton *valider;
    //QPushButton *annuler;
    QLineEdit* identifier;
    QLineEdit* title;
    QDateEdit* disponibility;
    QDateEdit* deadline;
    QListWidget* tasks;

    QFormLayout* formLayout;

public:
    NewProject(QWidget* parent = 0);
    const QLineEdit& getId() const { return *identifier; }
    const QLineEdit& getTitle() const { return *title; }
    const QDateEdit& getDisponibility() const { return *disponibility; }
    const QDateEdit& getDeadline() const { return *deadline; }
    QListWidget* getTasks() { return tasks; }
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
    QListWidget* predecessors;
    QCheckBox *preemtive;

    QFormLayout* formLayout;

public:
    NewTask(QWidget* parent = 0);
    const QComboBox& getType() const  { return *taskType; }
    const QLineEdit& getId() const { return *id; }
    const QLineEdit& getTitle() const { return *title; }
    const QTimeEdit& getDuration() const { return *duration; }
    const QDateEdit& getDisponibility() const { return *disponibility; }
    const QDateEdit& getDeadline() const { return *deadline; }
    const QListWidget& getPredecessors() const { return *predecessors; }
    const QCheckBox& getPreemtive() const { return *preemtive; }
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
   const QComboBox& getType() const  { return *type; }
   const QLineEdit& getId() const { return *id; }
   const QLineEdit& getTitle() const { return *title; }
   const QDateEdit& getDate() const { return *date; }
   const QTimeEdit& getTime() const { return *time; }
   const QTimeEdit& getDuration() const { return *duration; }
   const QLineEdit& getPlace() const { return *place; }
   const QLineEdit& getPeople() const { return *people; }
};

class NewProgrammation : public QDialog {
    Q_OBJECT
    QDialogButtonBox* buttonBox;

    QTimeEdit *schedule;
    QDateEdit* date;

    QFormLayout* formLayout;

public:
    NewProgrammation(QWidget* parent);
    const QTimeEdit& getSchedule() const { return *schedule; }
    const QDateEdit& getDate() const { return *date; }
};

#endif // WINDOW_H
