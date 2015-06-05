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

using namespace std;
using namespace TIME;

class Tache {
    /*! \class Tache
            \brief Classe permettant de manipuler des tâches
    */
    friend class TacheManager;
    //attributs
    QString id;
    QString titre;
    Duree duree;
    Date disponibilite;
    Date echeance;
    Tache(const Tache& t); //pas implémentée
    Tache& operator=(const Tache&); //pas implémentée
    //méthodes
    //les méthodes set sont privées car c'est TacheManager qui gère les Tache
    void setId(const QString& str);
    void setTitre(const QString& str) { titre = str; }
    inline void setDisponibilite(const Date& d);
    inline void setEcheance(const Date& e);
    virtual void setDuree(const Duree& d) { duree = d; }
    Tache(const QString& t, const Duree& dur, const Date& dispo, const Date& deadl):titre(t),duree(dur),disponibilite(dispo),echeance(deadl)
    { QUuid u=QUuid::createUuid(); this->id=u.toString(); } // probleme car l'heritage private n'est plus un heritage est un mais en terme de
public:
    const QString getId() const { return id; }
    const QString getTitre() const { return titre; }
    const Duree getDuree() const { return duree; }
    const Date getDisponibilite() const { return disponibilite; }
    const Date getEcheance() const { return echeance; }
    virtual QString toString() const=0;
};

QTextStream& operator<<(QTextStream& fout, const Tache& t);

//******************************************************************************************

class TacheU : public Tache , public Event {
    /*! \class TacheU
            \brief Classe permettant de manipuler des tâches unitaires
    */
    friend class TacheManager;
    //attributs
    bool preemptive;
    bool programmee;
    //méthodes
    void setProgrammee() { programmee = true; }
    void setNonProgrammee() { programmee = false; }
    void setDuree(const Duree& d); //redéfinition
    void setPreemptive() { preemptive = true;}
    inline void setNonPreemptive();
    TacheU(const QString& t, const Duree& dur, const Date& dispo, const Date& deadline, bool pre=false, bool prog=false):
        Tache(t,dur,dispo,deadline), preemptive(pre), programmee(prog)
    {
        if ((preemptive == false) && (getDuree().getDureeEnHeures() > 12))
                throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
    }
    TacheU (Tache& t, bool pre=false, bool prog=false):
        Tache(t.getTitre(),t.getDuree(),t.getDisponibilite(),t.getEcheance()), preemptive(pre), programmee(prog){}
public:
    const bool isPreemptive() const { return preemptive; }
    const bool isProgrammee() const { return programmee; }
    QString toString() const;
};

//******************************************************************************************

class TacheC : public Tache {
    /*! \class TacheC
            \brief Classe permettant de manipuler des tâches composites
    */
    friend class TacheManager;
    typedef std::vector<Tache *> vectcomp;
    //attributs
    vectcomp tachescomp;
    //méthodes
    ~TacheC() { tachescomp.clear(); } //clear() vide le contenu du conteneur
    TacheC(const QString& t, const Duree& dur, const Date& dispo, const Date& deadl): Tache(t,dur,dispo,deadl)
    { tachescomp.reserve(10); }
public:
    template <class T> void addTasktoC(const T& t) { tachescomp.push_back(t); }
    QString toString() const;
};

//******************************************************************************************

class TacheManager {
    /*! \class TacheManager
            \brief Classe permettant de créer, modifier et détruire des tâches
    */
    typedef std::vector<Tache*> tabtaches;
    //attributs
    tabtaches taches;
    QString file;
    struct Handler
    {
       TacheManager* instance;
       Handler():instance(0){}
       ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
    };
    static Handler handler;
    //méthodes
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

