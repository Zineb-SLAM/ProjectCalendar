#include "show_info.h"
#include "calendar.h"
#include "timing.h"
#include "tache.h"
#include "projet.h"
#include"programmation.h"
#include<QLabel>


ProjetInfo::ProjetInfo(const QString& i,QWidget *parent,Qt::WindowFlags f) : QDialog(parent,f)
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
TacheInfo::TacheInfo(Tache* t,QWidget *parent) : QDialog(parent) {
    this->setWindowTitle("Task "+t->getId());


        QString temp = "";
         id = new QLabel(t->getId(),this);
         titre = new QLabel(t->getTitre(),this);
         unsigned int H = t->getDuree().getHeure();
         unsigned int M = t->getDuree().getMinute();
        QString h = (H<10)?"0"+QString::number(H):""+QString::number(H);
        QString m = (M<10)?"0"+QString::number(M):""+QString::number(M);
        duree = new QLabel(h+" H "+m,this);
        disponibilite = new QLabel(t->getDisponibilite().toString(),this);
        echeance = new QLabel(t->getEcheance().toString(),this);
        if (!t->getTypeTache()) //composite
        {
             type = new QLabel("composite",this);
             TacheC* tempTask = dynamic_cast<TacheC*>(t);
            temp = "";
             for(std::vector<Tache *>::iterator it= tempTask->getCTaches().begin();it!= tempTask->getCTaches().end();it++)
            {
                temp += " "+(*it)->getId();
            }
            taches = new QLabel(temp,this);
        }
        if (t->getTypeTache())
        {
            type = new QLabel("unitary",this);
            TacheU* tempTask = dynamic_cast<TacheU*>(t);
            if (tempTask->isPreemptive()) preemtive = new QLabel("oui",this);
             if (!(tempTask->isPreemptive())) preemtive = new QLabel("non",this);


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


