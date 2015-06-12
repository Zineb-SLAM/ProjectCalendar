#include "ui_splitter.h"
#include "splitter.h"
#include "calendar.h"
#include "timing.h"
#include "tache.h"
#include "projet.h"
#include<QTableView>
#include<QListView>
#include<QHBoxLayout>
#include<QSplitter>
#include<QPushButton>
#include<QDialog>
#include<QFlags>
#include<QLabel>
#include <QListWidgetItem>


splitter::splitter (QWidget* parent, Qt::WindowFlags flags): QDialog(parent,flags),PM(ProjetManager::getInstance())
{
    QApplication::setStyle("plastique");

    QListWidget* listView = new QListWidget;//widget1
    QTableView* tableView = new QTableView;//widget2

    widget1 = new QListWidget;
    QHBoxLayout* w1Layout = new QHBoxLayout;

    widget2 = new QWidget;
    QHBoxLayout* w2Layout = new QHBoxLayout;
    w2Layout->addWidget(tableView);
    widget2->setLayout(w2Layout);


    QSplitter *mainSplitter = new QSplitter(this);
    mainSplitter->addWidget(widget1);
    mainSplitter->addWidget(widget2);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mainSplitter);


    setLayout(mainLayout);
}
void splitter::showProjects()
{
    for (std::vector<Projet*>::iterator it = PM.getTab().begin(); it!=PM.getTab().end(); ++it)
    {
        QListWidgetItem *item = new QListWidgetItem();
         item->setData(Qt::DisplayRole, (*it)->getId());// Ceci est le titre
         item->setData(Qt::UserRole + 1, (*it)->getTitre());// Ceci est la description
         widget1->addItem(item);
    }

      widget1->showMaximized();
}



void splitter::showTasks(Tache *t)
{
    this->setWindowTitle("Task "+t->getId());
    QLabel* id = new QLabel(t->getId(),this);
    QLabel*titre = new QLabel(t->getTitre(),this);

    if (!t->getTypeTache())
    {
         QLabel*type = new QLabel("composite",this);
         TacheC* tempC = dynamic_cast<TacheC*>(t);

        for (std::vector<Tache *>::iterator it=tempC->getCTaches().begin();it!=tempC->getCTaches().end();it++)
        {
           // (*it)->getId();
        }

    }

    if (t->getTypeTache()) // ICI DECLENCHER NOUVEAU WIDGET!!
    {

        TacheU* tempU = dynamic_cast<TacheU*>(t);
        //faire appel a Task info

    }

}

void Unitary::TaskInfo(TacheU *t)
{
    this->setWindowTitle("Tache_Unitaire "+t->getId());


    QLabel* id = new QLabel(t->getId(),this);
    QLabel*titre = new QLabel(t->getTitre(),this);
    QLabel* disponibilite = new QLabel(t->getDisponibilite().toString(),this);
    QLabel* echeance= new QLabel(t->getEcheance().toString(),this);

         QLabel*taskType = new QLabel("unitary",this);

        if (t->isPreemptive())  QLabel* type = new QLabel("preemptive",this);
        if (!(t->isPreemptive()))  QLabel* type = new QLabel("non preemptive",this);

    std::vector<TacheU *> precedence= t->getPrecedence();
    std::vector<TacheU *> suivante = t->getSuivante();

    for ( std::vector<TacheU *>::iterator it = precedence.begin(); it != precedence.end(); ++it)
    {
       //Afficher Id et Titre
    }

    for (std::vector<TacheU *>::iterator it = suivante.begin(); it != suivante.end(); ++it)
    {

            //afficher Id et Titre
    }

}



