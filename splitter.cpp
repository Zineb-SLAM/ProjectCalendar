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
    connect(widget1, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this, SLOT(showProjects()));

    widget2 = new TasksPart;
    QHBoxLayout* w2Layout = new QHBoxLayout;
    widget2->setLayout(w2Layout);
    QListWidgetItem *item2 = new QListWidgetItem();
    item2->setData(Qt::DisplayRole,"Mes Taches de Projets");
    widget2->addItem(item2);

    QSplitter *mainSplitter = new QSplitter(this);
    mainSplitter->addWidget(widget1);
    mainSplitter->addWidget(widget2);



    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mainSplitter);

    setLayout(mainLayout);
}



TasksPart:: TasksPart(QWidget* parent):QListWidget(parent)
{

}

void splitter::showProjects()
{
  widget1->clear();
 widget1-> setWindowTitle("Affichage des Projets");

    for (std::vector<Projet*>::iterator it = PM.getTab().begin(); it!=PM.getTab().end(); ++it)
    {
        QListWidgetItem *item = new QListWidgetItem();
         item->setData(Qt::DisplayRole, (*it)->getTitre());
        // item->setData(Qt::UserRole + 1, (*it)->getId());// Ceci est la description
         item->setWhatsThis((*it)->getId());
         widget1->addItem(item);
         QPushButton *button = new QPushButton("show",widget1);
         QString text ((*it)->getId());
         button->setText(text);


        // connect(this,SIGNAL(mousePressEvent(QMouseEvent*)),widget2,SLOT(showTasks(QListWidgetItem * item)));


    }
widget1->showMaximized();

}

void TasksPart::showTasks(QListWidgetItem * item)
{
    clear();
    ProjetManager& PM= ProjetManager::getInstance();
    QListWidgetItem *item2 = new QListWidgetItem();
    item2->setData(Qt::DisplayRole,"teeeest");
    addItem(item2);
    const QString& s =item->whatsThis();
    Projet* p= PM.getProjet(s);
    this->setWindowTitle("Taches du Projet "+p->getId());
    QMessageBox::information(NULL,"QTableView Item Clicked",s);

    for (std::vector<Tache*>::iterator it = p->GetTabProjet().begin(); it!=p->GetTabProjet().end(); ++it)
    {
        QListWidgetItem *item2 = new QListWidgetItem();
         item2->setData(Qt::DisplayRole, (*it)->getId());// Ceci est le titre
         item2->setData(Qt::UserRole + 1, (*it)->getTitre());// Ceci est la description
         addItem(item2);
    }

    /*for (unsigned int i =0;i< p->GetTabProjet().size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem();
         item->setData(Qt::DisplayRole,p->getIndice(i)->getId());// Ceci est le titre
         item->setData(Qt::UserRole + 1, p->getIndice(i)->getTitre());// Ceci est la description
        item->setWhatsThis((p->getIndice(i)->getId()));
         addItem(item);
    }*/
     showMaximized();


 }

void TasksPart::showTask(QListWidgetItem * item)
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
             addItem(item);
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



