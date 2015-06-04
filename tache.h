#ifndef TACHE_H
#define TACHE_H

#include <QString>
#include <QTextStream>
#include <vector>
#include <QUuid>
#include <sstream>
#include "timing.h"
#include "calendar.h"
#include "evenement.h"
#include "programmation.h"
#include "projet.h"
#include "timing.h"

using namespace std;
using namespace TIME;

class Tache
{
    friend class TacheManager;
    QString id;
    QString titre;
    Duree duree;
    Date disponibilite;
    Date echeance;
    Tache(const Tache& t); //pas implémentée
    Tache& operator=(const Tache&); //pas implémentée
protected:
    Tache(const QString& t, const Duree& dur, const Date& dispo, const Date& deadl):titre(t),duree(dur),disponibilite(dispo),echeance(deadl)
    { QUuid u=QUuid::createUuid(); this->id=u.toString(); } // probleme car l'heritage private n'est plus un heritage est un mais en terme de
public:
    const QString getId() const { return id; }
    //pas de setId : l'utilisateur n'a pas le droit de modifier l'id : void setId(const QString& str);
    const QString getTitre() const { return titre; }
    void setTitre(const QString& str) { titre = str; }
    const Duree getDuree() const { return duree; }
    virtual void setDuree(const Duree& d) { duree = d; } // Pourquoi virtual?
    const Date getDisponibilite() const { return disponibilite; }
    const Date getEcheance() const { return echeance; }
    inline void setDisponibilite(const Date& d);
    inline void setEcheance(const Date& e);
    virtual std::string toString() const=0;
};

QTextStream& operator<<(QTextStream& fout, const Tache& t);

//******************************************************************************************

class TacheU : public Tache , public Event
{
    bool preemptive;
    bool programmee;

    void setProgrammee();
                 //{ programmee = true;}
    void setNonProgrammee()
                    { programmee = false; }
 public:
//<<<<<<< Updated upstream
    TacheU(const QString& t, const Duree& dur, const Date& dispo, const Date& deadline, bool pre=false, bool prog=false):
        Tache(t,dur,dispo,deadline), preemptive(pre), programmee(prog)
    {
        if ((preemptive == false) && (getDuree().getDureeEnHeures() > 12))
                throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
    }
    TacheU (Tache& t, bool pre=false, bool prog=false):
        Tache(t.getTitre(),t.getDuree(),t.getDisponibilite(),t.getEcheance()), preemptive(pre), programmee(prog){}

    void setDuree(const Duree& d); //redéfinition
    const bool isPreemptive() const { return preemptive; }
    const bool isProgrammee() const { return programmee; }
    void setPreemptive() { preemptive = true;}
    void setNonPreemptive()
    {
        if(getDuree().getDureeEnHeures() > 12)
            throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
        preemptive = false;
    }


    /*QString toString() const
    {
        QTextStream f;
        f<<"**Tache Unitaire** \n";
        if(isPreemptive()) f<<"Tache Preemtive \n";
        if(isProgrammee()) f<<"Tache Programmee \n";
        QString s;
        f >> s;
    }*/



    std::string toString() const
        {

            std::stringstream f;
            f<<"**Tache Unitaire** \n";
            if(isPreemptive()) f<<"Tache Preemtive \n";
            if(isProgrammee()) f<<"Tache Programmee \n";
            return f.str();
        }

};

//******************************************************************************************

class TacheC : public Tache //clone
{
    typedef std::vector<Tache *> vectcomp;
    vectcomp tachescomp;
protected: TacheC(const QString& t, const Duree& dur, const Date& dispo, const Date& deadl): Tache(t,dur,dispo,deadl)
    { tachescomp.reserve(10); }
public:
    //bool Precedence(const Tache& t);
    template <class T> void addTasktoC(const T& t)
    {
        tachescomp.push_back(t);
    }
    std::string toString() const {
        std::stringstream f;
        f<<"**Tache Composite** \n";
        for(vectcomp::const_iterator it= tachescomp.begin(); it!=tachescomp.end();++it)
        {
            f<<(*it);
        }
        return f.str();
    }
    ~TacheC() { tachescomp.clear(); } //clear() vide le contenu du conteneur
};

//******************************************************************************************

class TacheManager
{
    typedef std::vector<Tache*> tabtaches;
    tabtaches taches;
    QString file;
    struct Handler
    {
       TacheManager* instance;
       Handler():instance(0){}
       ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
    };
    static Handler handler;
    TacheManager(const TacheManager& m);
    TacheManager& operator=(const TacheManager& m);
public:
    TacheManager();
    static TacheManager& getInstance();
    static void libererInstance();
    TacheU& ajouterTacheU(const QString& t, const Duree& dur, const Date& dispo, const Date& deadline, bool preempt, bool prog)
    {
        TacheU* newt = new TacheU(t,dur,dispo,deadline,preempt, prog);
        addItem(newt);
        return *newt;
    }
     template <class T> void addItem(T* t) //à adapter selon TacheU ou TacheC --> design pattern
    {
        taches.push_back(t);
    }
    void load(const QString& f);
    void save(const QString& f);
     void afficher(QTextStream& f) const { f<<"****TacheManager*****";}

    Tache& getTache(const QString& id)
    {
       /*for(tabtaches::const_iterator it= taches.begin(); it!=taches.end();++it)
        {
                 if(it->getId()==id)
                     return *it; //drowbacks
         }*/


    }
};

//******************************************************************************************

#endif // TACHE_H

