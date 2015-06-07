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



Programmation* ProgrammationManager::trouverProgrammation(const Event& e) const {
    for(unsigned int i=0; i<tabprogs.size(); i++)
    if (&e==&tabprogs[i]->getEvent()) return tabprogs[i];
    return 0;
}

ProgrammationManager::~ProgrammationManager() {
    for(unsigned int i=0; i<tabprogs.size(); i++)
    delete tabprogs[i];
}

void ProgrammationManager::ajouterProgrammation (const Event& e, const Date& d, const Horaire& h)
{
    Programmation* newt = new Programmation(e,d,h);
    addprog(newt);
}

void ProgrammationManager::ajouterProgrammation (TacheU& t, const Date& d, const Horaire& h)
{
    if(t.isProgrammee()) throw CalendarException ("Cette Tache est deja Programmee");
    t.setProgrammee();
    
    for(vectProg::iterator it = tabprogs.begin(); it != tabprogs.end(); ++it)
    {
        if((*it)->getDate()>d || (((*it)->getDate()==d) && (*it)->getHoraire()<h))
        t.getPrecedence().push_back(it);
        if(((*it)->getDate()<d || (((*it)->getDate()==d) && (*it)->getHoraire()>h)) && t.cestunetache())
        it.getPrecedence().push_back(t);
        
    }
    
    Programmation* newt = new Programmation(t,d,h);
    addprog(newt);
}
void ProgrammationManager::addprog(Programmation* p)
{
    
    tabprogs.push_back(p);
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


