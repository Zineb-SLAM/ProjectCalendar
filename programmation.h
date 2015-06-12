#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H

#include <QString>
#include <QTextStream>
#include <vector>
#include <QUuid>
#include <sstream>
#include "calendar.h"
#include "evenement.h"
#include "tache.h"

using namespace std;
using namespace TIME;

class Programmation
{
    friend class ProgrammationManager;
    const Event* event;
    Date date;
    Horaire horaire;
    //constructeurs et destructeur en privé car les Programmations sont gérées par ProgrammationManager
    Programmation(const Event* e, const Date& d, const Horaire& h):event(e), date(d), horaire(h){}
    Programmation(const Programmation& e);
public:
    const Event* getEvent() const { return event; }
    const Date& getDate() const { return date; }
    const Date& getDate()  { return date; }
    const Horaire& getHoraire() { return horaire; }
    const Horaire& getHoraire() const { return horaire;}
    QTextStream& afficher(QTextStream& f)const ;
};
QTextStream& operator<<(QTextStream& fout, const Programmation* t);

//******************************************************************************************

class ProgrammationManager
{
    typedef std::vector<Programmation*> vectProg;
    vectProg tabprogs;
    ProgrammationManager(const ProgrammationManager& e);
    ProgrammationManager& operator=(const ProgrammationManager& e);
    struct Handler
    {
        ProgrammationManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
    };
    static Handler handler;
public:
    ProgrammationManager(){ tabprogs.reserve(10);};
    ~ProgrammationManager();
    static ProgrammationManager& getInstance();
    static void libererInstance();
    Programmation* trouverProgrammation(const Event* t);
    Programmation* getProg(const QString& id_evt);
    void ajouterProgrammation(TacheU* t, const Date& d, const Horaire& h);
    void ajouterProgrammation(Activite* a, const Date& d, const Horaire& h);
    void addprog(Programmation* p);
    QTextStream& afficher(QTextStream& f,const Event* t)
    {
       Programmation* a= trouverProgrammation(t);
      return a->afficher(f);
    }
};



//******************************************************************************************

#endif // PROGRAMMATION_H

