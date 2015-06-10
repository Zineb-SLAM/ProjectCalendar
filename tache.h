#ifndef TACHE_H
#define TACHE_H
#include <QString>
#include <QTextStream>
#include <vector>
#include <QUuid>
#include <sstream>
#include "calendar.h"
#include "evenement.h"
using namespace std;
using namespace TIME;

class Tache {
    /*! \class Tache
     \brief Classe permettant de manipuler des tâches
     */
    friend class TacheManager;
    friend class TacheC;friend class TacheU;
    //attributs
    QString id;
    QString titre;
    Duree duree;
    Date disponibilite;
    Date echeance;
    bool isCompleted;

    //méthodes
   Tache(const Tache& t); //pas implémentée: on ne devrait pas l'implementer car chaque tache unique -->id
    Tache& operator=(const Tache&); //pas implémentée:on ne devrait pas l'implementer car chaque tache unique -->id
    //les méthodes set sont privées car c'est TacheManager qui gère les Tache
    void setId(const QString& str);
    void setTitre(const QString& str) { titre = str; }
    inline void setDisponibilite(const Date& d);
    inline void setEcheance(const Date& e);

protected:
    Tache(const QString& t, const Duree& dur, const Date& dispo, const Date& deadl):titre(t),duree(dur),disponibilite(dispo),echeance(deadl),
    isCompleted(false)
    { QUuid u=QUuid::createUuid(); this->id=u.toString(); }
    virtual void setDuree(const Duree& d) { duree = d; }
    void setCompleted() {isCompleted = true;}
    virtual ~Tache(){};
    
public:
    virtual const QString& getId() const { return id; }
    virtual const QString& getTitre() const { return titre; }
    virtual const Duree& getDuree() const { return duree; }
    const Date getDisponibilite() const { return disponibilite; }
    const Date getEcheance() const { return echeance;}
    virtual QString toString() const=0;

    
};

QTextStream& operator<<(QTextStream& fout, const Tache* const t);

//******************************************************************************************

class TacheU : public Tache , public Event {
    /*! \class TacheU
     \brief Classe permettant de manipuler des tâches unitaires
     */
    friend class TacheManager;
    //attributs
    bool preemptive;
    unsigned int progression;
    vector<TacheU*> precedence;
    vector<TacheU*> suivante;// La prograssion est evaluee de 1 a 100 si la progression est 100 le projet va alors considerer la tache comme completed
    //méthodes
    void setDuree(const Duree& d); //redéfinition
    void setPreemptive() { preemptive = true;}
    inline void setNonPreemptive();
    TacheU(const QString& t, const Duree& dur, const Date& dispo, const Date& deadline, const bool& pre=false, const bool& prog=false):
    Tache(t,dur,dispo,deadline), Event(prog), preemptive(pre)
    {
        if ((preemptive == false) && (dur.getDureeEnHeures() > 12))
        throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
    }

    TacheU(const Tache& t, const bool& pre=false, const bool& prog=false):
    Tache(t.getTitre(),t.getDuree(),t.getDisponibilite(),t.getEcheance()), Event(prog), preemptive(pre),precedence(0), suivante(0) {}
public:
    void ajouterPrecedence(TacheU* t );
    void supprimerPrecedence(const QString& id);
    vector<TacheU*> getPrecedence(){ return precedence;}
    vector<TacheU*> getSuivante(){ return suivante;}
    void setProgression(unsigned int i)
    {
        if( i>100) throw CalendarException("Progression invalide la progression doit etre entre 0 et 100");
        if(progression>i) throw CalendarException("Impossible La prrogression a inserer doit être supérieure à la progression actuelle");
        progression=i;
    }
    unsigned int& getProgression() { return progression;}
    bool isPreemptive() const { return preemptive; }
    bool cestunetache() const { return true;}
    const QString& getId() const { return id; }
    const Duree& getDuree() const { return duree; }
    const QString& getTitre() const { return titre; }
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
    template <class T> void addTasktoC(const T& t) { tachescomp.push_back(t); }
public:
    QString toString() const;
};

//******************************************************************************************

class TacheManager
{
    /*! \class TacheManager
     \brief Classe permettant de créer, modifier et détruire des tâches
     */
    typedef std::vector<Tache*> tabtaches;
    struct Handler
    {
        TacheManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
    };
    //attributs
    tabtaches taches;
    QString file;
    static Handler handler;
    //méthodes
    TacheManager() { taches.reserve(10); }
    ~TacheManager() { taches.clear(); };
    TacheManager(const TacheManager& m);
    TacheManager& operator=(const TacheManager& m);
    template <class T> void addItem(T* t) { taches.push_back(t); }
public:
    static TacheManager& getInstance();
    static void libererInstance();
    TacheU& ajouterTacheU(const QString& t, const Duree& dur, const Date& dispo, const Date& deadline, const bool& preempt=false, const bool& prog=false);
    TacheC& ajouterTacheC(const QString& t, const Duree& dur, const Date& dispo, const Date& deadl);
    template <class T> void ajouterTacheATacheC(const TacheC& tacheC, const T& tacheAjout) {
        tacheC.addTasktoC(tacheAjout);
    }
    void load(const QString& f);
    void save(const QString& f);
    void afficher(QTextStream& f) const { f<<"****TacheManager*****"; }
    Tache& getTache(const QString& id);
    void ajouterPrecedenceTache(const Tache& tAjout, const Tache& tPrecedente);
};

//******************************************************************************************

#endif // TACHE_H

