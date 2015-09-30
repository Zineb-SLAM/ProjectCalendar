#include "show_info.h"
#include "calendar.h"
#include "timing.h"
#include "tache.h"
#include "projet.h"
#include"programmation.h"
#include<QLabel>


ProjetInfoId::ProjetInfoId(const QString& i,QWidget *parent,Qt::WindowFlags f) : QDialog(parent,f)
{
    ProjetManager& PM=ProjetManager::getInstance();
    Projet* p = PM.getProjet(i);
    QString temp = "";
    id = new QLabel( p->getId(),this);
    titre = new QLabel(p->getTitre(),this);
    disponibilite = new QLabel((p->getDisponibilite()).toString(),this);
    echeance = new QLabel((p->getEcheance()).toString(),this);


     for (std::vector<Tache*>::iterator itt = p->GetTabProjet().begin(); itt!=p->GetTabProjet().end(); ++itt)
     {
        temp += " "+(*itt)->getId();
     }

    taches = new QLabel(temp,this);

    formLayout = new QFormLayout(this);

    formLayout->addRow("id : ",id);
    formLayout->addRow("title : ",titre);
    formLayout->addRow("disponibilite",disponibilite);
    formLayout->addRow("echeance",echeance);
    formLayout->addRow("taches:",taches);

    setLayout(formLayout);

}

ProjetInfo::ProjetInfo(Projet *p,QWidget *parent,Qt::WindowFlags f) : QDialog(parent,f)
{

      QString temp = "";
     id = new QLabel( p->getId(),this);
     titre = new QLabel(p->getTitre(),this);
     disponibilite = new QLabel((p->getDisponibilite()).toString(),this);
     echeance = new QLabel((p->getEcheance()).toString(),this);


     for (std::vector<Tache*>::iterator itt = p->GetTabProjet().begin(); itt!=p->GetTabProjet().end(); ++itt)
     {
        temp += " "+(*itt)->getId();
     }

    taches = new QLabel(temp,this);

    formLayout = new QFormLayout(this);

    formLayout->addRow("id : ",id);
    formLayout->addRow("title : ",titre);
    formLayout->addRow("disponibilite",disponibilite);
    formLayout->addRow("echeance",echeance);
    formLayout->addRow("taches:",taches);

    setLayout(formLayout);

}
TacheInfo::TacheInfo(Tache* t,QWidget *parent,Qt::WindowFlags f): QDialog(parent,f)
{
    this->setWindowTitle("Task "+t->getId());


        if (t->getTypeTache()) //composite
        {
             type = new QLabel("composite",this);
             TacheU* tempTask = dynamic_cast<TacheU*>(t);
            QString temp = "";
            temp = "";
             id = new QLabel(tempTask->getId(),this);
             titre = new QLabel(tempTask->getTitre(),this);
            duree = new QLabel(tempTask->getDuree().toString(),this);
            disponibilite = new QLabel(tempTask->getDisponibilite().toString(),this);
            echeance = new QLabel(tempTask->getEcheance().toString(),this);
            temp = "";
            for ( std::vector<TacheU *>::iterator it = tempTask->getPrecedence().begin(); it != tempTask->getPrecedence().end(); ++it)
            {
               temp += " "+(*it)->getId();
               }
            precedente = new QLabel(temp,this);
            temp = "";
            for (std::vector<TacheU *>::iterator it = tempTask->getSuivante().begin(); it != tempTask->getSuivante().end(); ++it)
            {
              temp += " "+(*it)->getId();
              }
              suivante = new QLabel(temp,this);
               formLayout = new QFormLayout(this);

        }
        else
        {
            type = new QLabel("composite",this);
             TacheC* tempTask = dynamic_cast<TacheC*>(t);
             QString temp = "";
                        temp = "";


                         id = new QLabel(tempTask->getId(),this);
                         titre = new QLabel(tempTask->getTitre(),this);
                        duree = new QLabel(tempTask->getDuree().toString(),this);
                        disponibilite = new QLabel(tempTask->getDisponibilite().toString(),this);
                        echeance = new QLabel(tempTask->getEcheance().toString(),this);
                         for(std::vector<Tache *>::iterator it= tempTask->getCTaches().begin();it!= tempTask->getCTaches().end();it++)
                        {
                            temp += " "+(*it)->getId();
                        }
                        taches = new QLabel(temp,this);
                        formLayout = new QFormLayout(this);

        }

    formLayout->addRow("id : ",id);
    formLayout->addRow("tirle : ",titre);
    formLayout->addRow("duree",duree);
    formLayout->addRow("disponibilite",disponibilite);
    formLayout->addRow("echeance",echeance);
    formLayout->addRow("type : ",type);
    formLayout->addRow("preemtive : ",preemtive);
    formLayout->addRow("precedentes : ",precedente);
    formLayout->addRow("suivantes",suivante);

    setLayout(formLayout);
}

