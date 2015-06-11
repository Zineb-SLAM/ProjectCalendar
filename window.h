#ifndef WINDOW_H
#define WINDOW_H
#include"calendar.h"
#include"timing.h"
#include"programmation.h"
#include"projet.h"
#include"tache.h"
#include"evenement.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTreeView>
#include <QTableWidget>
#include <QDialog>
#include <QFormLayout>
#include <QTimeEdit>
#include <QDateEdit>
#include <QMessageBox>
#include <QListWidget>
#include <QListView>
#include <QDialogButtonBox>
#include <QPoint>
#include <QMenu>
#include<QSpinBox>
#include <math.h>
#include <QTableView>


class NewProject: public QDialog {
    Q_OBJECT
    QDialogButtonBox* buttonBox;
    QLineEdit* identifier;
    QLineEdit* title;
    QTimeEdit* duration;
    QDateEdit* disponibility;
    QDateEdit* deadline;
    QListView* tasks;

    QLabel* identifierL;
    QLabel* titleL;
    QLabel* durationL;
    QLabel* disponibilityL;
    QLabel* deadlineL;
    QLabel* tasksL;

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
    QSpinBox *durationH,*durationM;
    QDateEdit* disponibility;
    QDateEdit* deadline;
    QComboBox* taskType;
    QListView* tasks;
    QListView* precedecessor;
    QListView* successor;

    QLabel* idl;
    QLabel* titlel;
    QLabel* durationHl; QLabel* durationMl;
    QLabel* disponibilityl;
    QLabel* deadlineL;
    QLabel* tasksl;
    QLabel* taskTypel;
    QLabel* precedl;
    QLabel* succl;

    QFormLayout* formLayout;

public:
    NewTask(QWidget* parent = 0);
public slots:
    //void addNewTask();
};

class NewActivity : public QWidget {
    Q_OBJECT

    QComboBox* type;// RDV or Meeting
    QLineEdit* id;
    QLineEdit* name;
    QDateEdit* date;
    QTimeEdit* time;
    QSpinBox *durationH,*durationM;
    QLineEdit* place;
    QLineEdit* people;


    QLabel* typel;
    QLabel* idl;
    QLabel* namel;
    QLabel* datel;
    QLabel* timel;
    QLabel* durationHl; QLabel* durationMl;
    QLabel* placel;
    QLabel* peoplel;


public:
   NewActivity(QWidget* parent);

public slots:
    //void addNewActivity();
};

class NewProgrammation : public QWidget {
    Q_OBJECT

    QListView* events;// RDV or Meeting
    QSpinBox *scheduleH,*scheduleM;
    QLineEdit* date;

    QLabel* eventsl;
    QLabel* scheduleHl; QLabel* scheduleMl;
    QLabel* datel;

public:
    NewProgrammation(QWidget* parent);

public slots:
    //void addProgrammation();
};

class MainWindow:public QWidget
{
    QTreeView projectsview;
};

#endif // WINDOW_H
