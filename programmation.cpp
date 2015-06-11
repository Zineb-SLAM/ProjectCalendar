#include <vector>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QTextStream>
#include "Calendar.h"
#include "programmation.h"

using namespace TIME;

ProgrammationManager::Handler ProgrammationManager::handler=ProgrammationManager::Handler();

ProgrammationManager& ProgrammationManager::getInstance() {
    if (handler.instance==0) handler.instance=new ProgrammationManager();
    return *(handler.instance);
}

void ProgrammationManager::libererInstance() {
    if (handler.instance!=0) delete handler.instance;
    handler.instance=0;
}
 /*Programmation* ProgrammationManager::getProg(const QString& id_evt)
 {
     for(vector<Programmation*>::iterator it=tabprogs.begin(); it!=tabprogs.end();it++)
     {
        if((*it)->getEvent())
     }

 }*/
//Programmation* ProgrammationManager::trouverProgrammation(const Programmation* e)
Programmation* ProgrammationManager::trouverProgrammation(const Event* e)
{
    if(!e->estProgrammee()) throw CalendarException ("la tache n'est pas programmee");
    for( vector<Programmation*>::iterator it = tabprogs.begin(); it != tabprogs.end(); ++it)
    {
        if ((*it)->getEvent()==e)
        {
                return *it;
        }
    }
    return 0;
}

void ProgrammationManager::ajouterProgrammation(TacheU* t, const Date& d, const Horaire& h)
{
    if(t->estProgrammee()) throw CalendarException ("Cette Tache est deja Programmee");
    /*************Tache non Preemptive***********/
    if(t->isPreemptive())
    {
        std::cout<<"Entrer le nombre de minutes a programmer < 720 minutes \n";
        unsigned int nb;
        std::cin>>nb;
        if(nb>720) throw CalendarException("Entrer un nombre de Minutes < 720");
        Duree duree(nb);
        float n=t->getProgression()+((nb*100)/t->getDuree().getDureeEnMinutes());
        if(n>100) throw CalendarException("Impossible: Vous pouvez la finir en moins de temps");
        t->getProgression()+=n;
        if(t->getProgression()==100) t->setProgrammee();
        /********************Precedente****************/
         for( vector<TacheU*>::iterator it = t->getPrecedence().begin(); it != t->getPrecedence().end(); ++it)
       {
             if((*it)->estProgrammee())
            {
                 Programmation * prog= trouverProgrammation(*it);

                if((prog->getDate()<d))
                 {
                         Horaire* test= prog->getHoraire().getFin((*it)->getDuree()); //mon horaire apres avoir fini ma date
                        if(23>=test->getHeure()) //  meme apres avoir fini ma date (+duree) je reste dans le meme jour precedent
                        {
                            Programmation* newt = new Programmation(t,d,h);
                            addprog(newt);
                        }
                        else if(23<test->getHeure()) //  mais si elle est a cheval sur deux jours (exemple elle commence a 23h et a une duree de 4h et donc finit a 3h (27h)
                        {
                          unsigned int diff_h= test->getHeure()-24; // je convertis 27h45 à 3h45
                          Horaire testh=Horaire(diff_h,test->getMinute());// je reconstruis mon nouveau horaire qui sera dans le jour d'apres

                            if(testh<h || testh==h) // si la precedence finit a 3h et je commence ma tache a 4h c'est ok
                                {
                                    Programmation* newt = new Programmation(t,d,h);
                                    addprog(newt);
                                 }
                          else
                              throw CalendarException("Votre Programmation ne respecte pas le principe de Precedence");

                        }

                   }

                else if ((prog->getDate()==d) && (prog->getHoraire()<h) && ((*(prog->getHoraire().getFin((*it)->getDuree())))<h))// the first is obvious
                {
                    Programmation* newt = new Programmation(t,d,h);
                    addprog(newt);
                 }
                else
                     throw CalendarException("Votre Programmation ne respecte pas le principe de Precedence");

          }
       }

         /********************Suivante****************/
         for( vector<TacheU*>::iterator it = t->getSuivante().begin(); it != t->getSuivante().end(); ++it)
       {
             if((*it)->estProgrammee())
            {
                 Programmation * prog= trouverProgrammation(*it);

                if(d<prog->getDate())
                 {
                         Horaire* test=h.getFin(duree); //mon horaire apres avoir fini ma date a ajouter doit rester dans le jour precedent
                        if(23>=test->getHeure()) //  meme apres avoir fini ma date (+duree) je reste dans le meme jour precedent
                        {
                            Programmation* newt = new Programmation(t,d,h);
                            addprog(newt);
                        }
                        else if(23<test->getHeure()) //  mais si elle est a cheval sur deux jours (exemple elle commence a 23h et a une duree de 4h et donc finit a 3h (27h)
                        {
                          unsigned int diff_h= test->getHeure()-24; // je convertis 27h45 à 3h45 (27-24=3)
                          Horaire testh=Horaire(diff_h,test->getMinute()); // je reconstruis mon nouveau horaire qui sera dans le jour d'apres

                            if(testh<prog->getHoraire()) // je finis ma tache que j'ajoute après le debut de sa tache suivante
                                {
                                    Programmation* newt = new Programmation(t,d,h);
                                    addprog(newt);
                                 }
                         else
                              throw CalendarException("Votre Programmation ne respecte pas le principe de Precedence");

                        }

                   }

                else if ((prog->getDate()==d) && (h<prog->getHoraire()) && ((*h.getFin((duree)))<prog->getHoraire()))
                {
                    Programmation* newt = new Programmation(t,d,h);
                    addprog(newt);
                 }
                else
                     throw CalendarException("Votre Programmation ne respecte pas le principe de Precedence");

          }
       }
    }
        /*************Tache non Preemptive***********/
    else
    {
        t->setProgrammee();
        t->setProgression(100);


     // il faut parcourir tous ses taches precedentes et taches suivantes --> Ma tache doit etre après TOUTES ses dates precedentes et avant TOUTES ses taches suivantes

        /********************Precedente****************/
         for( vector<TacheU*>::iterator it = t->getPrecedence().begin(); it != t->getPrecedence().end(); ++it)
       {
             if((*it)->estProgrammee())
            {
                 Programmation * prog= trouverProgrammation(*it);

                if((prog->getDate()<d))
                 {
                         Horaire* test= prog->getHoraire().getFin((*it)->getDuree()); //mon horaire apres avoir fini ma date
                        if(23>=test->getHeure()) //  meme apres avoir fini ma date (+duree) je reste dans le meme jour precedent
                        {
                            Programmation* newt = new Programmation(t,d,h);
                            addprog(newt);
                        }
                        else if(23<test->getHeure()) //  mais si elle est a cheval sur deux jours (exemple elle commence a 23h et a une duree de 4h et donc finit a 3h (27h)
                        {
                          unsigned int diff_h= test->getHeure()-24; // je convertis 27h45 à 3h45
                          Horaire testh=Horaire(diff_h,test->getMinute());// je reconstruis mon nouveau horaire qui sera dans le jour d'apres

                            if(h<testh || testh==h) // si la precedence finit a 3h et je commence ma tache a 4h c'est ok
                                {
                                    Programmation* newt = new Programmation(t,d,h);
                                    addprog(newt);
                                 }
                          else
                              throw CalendarException("Votre Programmation ne respecte pas le principe de Precedence");

                        }

                   }

                else if ((prog->getDate()==d) && (prog->getHoraire()<h) && ((*(prog->getHoraire().getFin((*it)->getDuree())))<h))
                {
                    Programmation* newt = new Programmation(t,d,h);
                    addprog(newt);
                 }
                else
                     throw CalendarException("Votre Programmation ne respecte pas le principe de Precedence");

          }
       }

         /********************Suivante****************/
         for( vector<TacheU*>::iterator it = t->getSuivante().begin(); it != t->getSuivante().end(); ++it)
       {
             if((*it)->estProgrammee())
            {
                 Programmation * prog= trouverProgrammation(*it);

                if(d<prog->getDate())
                 {
                         Horaire* test= h.getFin(t->getDuree()); //mon horaire apres avoir fini ma date a ajouter doit rester dans le jour precedent
                        if(23>=test->getHeure()) //  meme apres avoir fini ma date (+duree) je reste dans le meme jour precedent
                        {
                            Programmation* newt = new Programmation(t,d,h);
                            addprog(newt);
                        }
                        else if(23<test->getHeure()) //  mais si elle est a cheval sur deux jours (exemple elle commence a 23h et a une duree de 4h et donc finit a 3h (27h)
                        {
                          unsigned int diff_h= test->getHeure()-24; // je convertis 27h45 à 3h45 (27-24=3)
                          Horaire testh=Horaire(diff_h,test->getMinute()); // je reconstruis mon nouveau horaire qui sera dans le jour d'apres

                            if(testh<prog->getHoraire()) // je finis ma tache que j'ajoute après le debut de sa tache suivante
                                {
                                    Programmation* newt = new Programmation(t,d,h);
                                    addprog(newt);
                                 }
                         else
                              throw CalendarException("Votre Programmation ne respecte pas le principe de Precedence");

                        }

                   }

                else if ((prog->getDate()==d) && (h<prog->getHoraire()) && (h<(*(prog->getHoraire().getFin((*it)->getDuree())))))
                {
                    Programmation* newt = new Programmation(t,d,h);
                    addprog(newt);
                 }
                else
                     throw CalendarException("Votre Programmation ne respecte pas le principe de Precedence");

          }
       }
    }

 }

void ProgrammationManager::ajouterProgrammation(Activite* a, const Date& d, const Horaire& h)
{
    Programmation* newt = new Programmation(a,d,h);
    addprog(newt);
}


void ProgrammationManager::addprog(Programmation* p)
{
    
    tabprogs.push_back(p);
}

QTextStream& Programmation::afficher(QTextStream& fout) const
{
    fout<<this->getEvent()->getId()<<":  ";
    fout<<this->getEvent()->getTitre()<<"\n";
    this->getEvent()->getDuree().afficher(fout);
    fout<<"\n";
    getHoraire().afficher(fout);
    getDate().afficher(fout);
    //fout<<getHoraire()<<"\n";
    //fout<<getDate()<<"\n";
    fout<<"\n";
    fout<<"\n";
    return fout;
}

QTextStream& operator<<(QTextStream& fout, const Programmation* t)
{
    return t->afficher(fout);

}

ProgrammationManager::~ProgrammationManager()
{
    tabprogs.clear();
}


/*ProgrammationManager::ProgrammationManager(const ProgrammationManager& e) {
 tabprogs.reserve(e.tabprogs.size());
 for(unsigned int i=0; i<e.tabprogs.size(); i++)
 tabprogs[i] = new Programmation(*e.tabprogs[i]);
 }
 
 ProgrammationManager& ProgrammationManager::operator=(const ProgrammationManager& e) {
 if (this==&e) return *this;
 this->~ProgrammationManager();
 for(unsigned int i=0; i<e.tabprogs.size(); i++)
 addprog(new Programmation(*e.tabprogs[i]));
 return *this;
 }*/


