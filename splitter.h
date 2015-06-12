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

namespace Ui
{
class splitter;
}

class splitter : public QDialog
{
    Q_OBJECT
     ProjetManager& PM;
     QListWidget* widget1;
     QWidget* widget2;

public:
     splitter(QWidget *parent = 0, Qt::WindowFlags flags=0);
     //~splitter();

private:
    void showProjects();
    void showTasks(Tache *t);

signals:
        private slots:


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
