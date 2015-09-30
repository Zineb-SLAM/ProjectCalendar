#ifndef SPLITTER_H
#define SPLITTER_H
#include<QFlags>
#include <QDialog>
#include "calendar.h"
#include "timing.h"
#include "tache.h"
#include "projet.h"
#include<QListView>
#include<QListWidget>
#include<QWidget>
#include<QLabel>


namespace Ui
{
class splitter;
}



class splitter : public QWidget
{
    Q_OBJECT
     QListWidget* widget1;
     QListWidget* widget2;

     ProjetManager& PM;

public:
     splitter(QWidget *parent = 0, Qt::WindowFlags flags=0);
     //~splitter();

private:


public slots:
      void showProjects();
     void show_project_info(QListWidgetItem * item);
     void showTasks();
      void showTask(QListWidgetItem* item);

     };




class Unitary: public QDialog
{
    QWidget* widget;

public:
     Unitary(QDialog *parent = 0);
      ~Unitary();

private:
   void TaskInfo(TacheU *t);

};




#endif // SPLITTER_H
