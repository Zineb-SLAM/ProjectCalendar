#include "ui_splitter.h"
#include "splitter.h"
#include "calendar.h"
#include "timing.h"
#include "tache.h"
#include "projet.h"
#include"show_info.h"
#include<QTableView>
#include<QListView>
#include<QHBoxLayout>
#include<QSplitter>
#include<QPushButton>
#include<QDialog>
#include<QFlags>
#include<QLabel>
#include <QListWidgetItem>
#include<QMessageBox>
splitter::splitter (QWidget* parent, Qt::WindowFlags flags): QWidget(parent,flags), PM(ProjetManager::getInstance())
{
    QApplication::setStyle("plastique");

    widget1 = new QListWidget;
    QHBoxLayout* w1Layout = new QHBoxLayout;
    widget1->setLayout(w1Layout);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::DisplayRole,"Mes Projets");
    widget1->addItem(item);

    connect(widget1, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(showProjects()));
   connect(widget1, SIGNAL(),this, SLOT(showTasks()));

    widget2 = new QListWidget;
    QHBoxLayout* w2Layout = new QHBoxLayout;
    widget2->setLayout(w2Layout);


    QSplitter *mainSplitter = new QSplitter(this);
    mainSplitter->addWidget(widget1);
    mainSplitter->addWidget(widget2);

    QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget(mainSplitter);

    //connect(widget1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showTasks(QListWidgetItem * item)));
   // connect(widget1,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(show_project_info(QListWidgetItem * item)));

    setLayout(mainLayout);
}


void splitter::showProjects()
{

  widget1->clear();
  //widget2->clear();
 widget1-> setWindowTitle("Affichage des Projets");
QMessageBox::information(NULL,"QTableView Item Clicked","hello 1");


    for (std::vector<Projet*>::iterator it = PM.getTab().begin(); it!=PM.getTab().end(); ++it)
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::DisplayRole, (*it)->getTitre());
        item->setData(Qt::UserRole + 1, (*it)->getId());// Ceci est la description
        item->setWhatsThis((*it)->getId());
        widget1->addItem(item);
        /*QListWidgetItem *item2 = new QListWidgetItem();
       item2->setData(Qt::DisplayRole,"Mes Taches de Projets");
        widget2->addItem(item2); */

        widget1->showMaximized();

}
        /*for (unsigned int i =0;i< (*it)->GetTabProjet().size(); i++)
        {
    QListWidgetItem *item3 = new QListWidgetItem();
    item3->setData(Qt::UserRole + 1, (*it)->getIndice(1)->getTitre());
    widget2->addItem(item3);


        //}*/

    }

void splitter::show_project_info(QListWidgetItem * item)
{
    const QString& s =item->whatsThis();
    Projet* p= PM.getProjet(s);
    ProjetInfo info(p);
    info.show();



}

void  splitter::showTasks()
{
    QMessageBox::information(NULL,"QTableView Item Clicked","hello 2");
   widget2->clear();
    for (std::vector<Projet*>::iterator it = PM.getTab().begin(); it!=PM.getTab().end(); ++it)
    {
        for (unsigned int i =0;i< (*it)->GetTabProjet().size(); i++)

        {
            QListWidgetItem *item2 = new QListWidgetItem();
           item2->setData(Qt::DisplayRole, (*it)->getIndice(i)->getId());// Ceci est le titre
           item2->setData(Qt::UserRole + 1, (*it)->getIndice(i)->getTitre());// Ceci est la description
           widget2-> addItem(item2);
        }
    }




  /*  const QString& s =item->whatsThis();
    Projet* p= PM.getProjet(s);
    this->setWindowTitle("Taches du Projet "+p->getId());

    for (std::vector<Tache*>::iterator it = p->GetTabProjet().begin(); it!=p->GetTabProjet().end(); ++it)
    {
        QListWidgetItem *item2 = new QListWidgetItem();
         item2->setData(Qt::DisplayRole, (*it)->getId());// Ceci est le titre
         item2->setData(Qt::UserRole + 1, (*it)->getTitre());// Ceci est la description
        widget1-> addItem(item2);
    }*/


    widget2->showMaximized();
 }

void  splitter::showTask(QListWidgetItem * item)
{
    TacheManager& M=  TacheManager::getInstance();
    const QString& s =item->whatsThis();
    Tache* t= M.getTache(s);
    if (!t->getTypeTache()) // Si c'est une tache composite
    {
         QLabel*type = new QLabel("composite",this);
         TacheC* tempC = dynamic_cast<TacheC*>(t);

        for (std::vector<Tache *>::iterator it=tempC->getCTaches().begin();it!=tempC->getCTaches().end();it++)
        {
            QListWidgetItem *item = new QListWidgetItem();
             item->setData(Qt::DisplayRole, (*it)->getId());// Ceci est le titre
             item->setData(Qt::UserRole + 1, (*it)->getTitre());// Ceci est la description
             item->setWhatsThis(((*it)->getId()));
             widget2->addItem(item);
        }

    }

    if (t->getTypeTache()) // ICI DECLENCHER NOUVEAU WIDGET!!
    {

        TacheU* tempU = dynamic_cast<TacheU*>(t);
        //faire appel a Task info de Unitary

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



