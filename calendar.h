#ifndef CALENDAR_H
#define CALENDAR_H
#include <QString>
#include <QTextStream>
#include <vector>
#include <QUuid>
#include <sstream>
#include "timing.h"

using namespace std;
using namespace TIME;

//******************************************************************************************
class CalendarException {
    QString info;
public:
    CalendarException(const QString& message) : info(message) {}
    QString getInfo() const { return info; }
};

//******************************************************************************************
class Tache {
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
    virtual void setDuree(const Duree& d) { duree = d; }
    const Date getDisponibilite() const { return disponibilite; }
    const Date getEcheance() const { return echeance; }
    inline void setDisponibilite(const Date& d);
    inline void setEcheance(const Date& e);
    virtual QString toString() const=0;
};

QTextStream& operator<<(QTextStream& fout, const Tache& t);

//******************************************************************************************
class Event  // CLASSE ABSTRAITE
{

 public:
};

class Activite: public Event {
    QString id;
    QString titre;
    Duree duree;
    QString lieu;
public:
    Activite(const QString& t, const Duree d, const QString& l):id(id), titre(t), duree(d), lieu(l) {
        QUuid u=QUuid::createUuid(); this->id=u.toString(); }
    const QString& getId() const { return id; }
    const QString& getTitre() const { return titre; }
    const Duree& getDuree() const { return duree; }
    const QString& getLieu() const { return lieu; }
    virtual void Afficher_Activite () const =0;
};

class Rdv : public Activite {
    QString personne;
public:
    Rdv(const QString& t, const Duree d, const QString& l, const QString& p):Activite(t,d,l), personne(p) {}
};

class Reunion : public Activite {
public:
    Reunion(const QString& t, const Duree d, const QString& l):Activite(t,d,l) {}
};


//******************************************************************************************
class TacheU : public Tache , public Event {
    bool preemptive;
    bool programmee;
 public:
    TacheU(const QString& t, const Duree& dur, const Date& dispo, const Date& deadline, bool pre=false, bool prog=false):
        Tache(t,dur,dispo,deadline), preemptive(pre), programmee(prog)
    {
        if ((preemptive == false) && (getDuree().getDureeEnHeures() > 12))
                throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
    }
    TacheU(Tache& t, bool pre=false, bool prog=false):Tache(t.getTitre(),t.getDuree(),t.getDisponibilite(),t.getEcheance()), preemptive(pre), programmee(prog){}
    void setDuree(const Duree& d); //redéfinition
    const bool isPreemptive() const { return preemptive; }
    const bool isProgrammee() const { return programmee; }
    void setPreemptive() {
        if(getDuree().getDureeEnHeures() > 12)
            throw CalendarException ("Duree de la tache inferieur a 12");
        preemptive = true;
    }
    void setNonPreemptive() {
        if(getDuree().getDureeEnHeures() > 12)
            throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
        preemptive = false;
    }
    void setProgrammee() { programmee = true; }
    void setNonProgrammee() { programmee = false; }
    QString toString() const {
        QTextStream f;
        f<<"**Tache Unitaire** \n";
        if(isPreemptive()) f<<"Tache Preemtive \n";
        if(isProgrammee()) f<<"Tache Programmee \n";
        QString s;
        f >> s;
    }
};

template <class T>
class TacheC : public Tache //clone
{
    typedef std::vector<Tache *> vectcomp;
    vectcomp tachescomp;
    TacheC(const QString& t, const Duree& dur, const Date& dispo, const Date& deadl): Tache(t,dur,dispo,deadl)
    { tachescomp.reserve(10); }
public:
    //bool Precedence(const Tache& t);
    void addTasktoC(const T& t) {
        tachescomp.push_back(t);
    }
    QString toString() const {
        QTextStream f;
        f<<"**Tache Composite** \n";
        for(vectcomp::const_iterator it= tachescomp.begin(); it!=tachescomp.end();++it) {
            f<<(*it);
        }
        return f.str();
    }
    ~TacheC() { tachescomp.clear(); } //clear() vide le contenu du conteneur
};

//******************************************************************************************
class VPrincipale { // class abstraite pour le tableau de taches
    typedef std::vector<Tache*> tabtaches;
    tabtaches taches;
    QString file;
public:
    void addItem(Tache* t);
    //Tache* trouverTache(const QString& id) const;
    VPrincipale() { taches.reserve(10); }
    VPrincipale(const QString& f): file(f) { taches.reserve(10); }
    virtual ~VPrincipale();
    //VPrincipale(const VPrincipale& m);
    //VPrincipale& operator=(const VPrincipale& m);
    TacheU& ajouterTacheU(const QString& t, const Duree& dur, const Date& dispo, const Date& deadline, bool preempt=false, bool prog=false);
    //Tache& getTache(const QString& id);
    //bool isTacheExistante(const QString& id) const { return trouverTache(id)!=0; }
    const Tache& getTache(const QString& code) const;
    void load(const QString& f);
    void save(const QString& f);
    virtual void afficher(QTextStream& f) const =0;

};

//******************************************************************************************
class Projet: public VPrincipale // On herite de l'interface et du comportement
{
    friend class ProjetManager;
    QString id;
    QString titre;
    Date disponibilite;
    Date echeance;
    struct Handler
     {
        Projet* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
     };
    static Handler handler;
    Projet(const QString& t,const Date& disp, const Date& ech):id(id), titre(t), disponibilite(disp), echeance(ech),VPrincipale()
    { QUuid u=QUuid::createUuid(); this->id=u.toString(); }
public:
    //static Projet& getInstance();
    //static void libererInstance();
    const QString& getId() const { return id; }
    const QString& getTitre() const { return titre; }
    const Date& getDisponibilite() const { return disponibilite; }
    const Date& getEcheance() const { return echeance; }
    void setDisponbilite(Date d) { this->disponibilite=d; }
    void setEcheance (Date e) { this->echeance=e; }
    void afficher(QTextStream& f) const {
        f<<"****Projet*****";
    }
};


class ProjetManager: public VPrincipale {
    typedef std::vector<Projet*> TabProjet;
    TabProjet tabprojets;
    struct Handler {
        ProjetManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
    };
    static Handler handler;
public:
    //static ProjetManager& getInstance();
    //static void libererInstance();
    void afficher(QTextStream& f) const {
        f<<"****ProjetManaeger*****";
    }
    //void ajouterProjet(const QString& id, const QString& t,const Date& disp, const Date& ech);
    //Projet& getProjet(const QString& id);
};

//******************************************************************************************
class TacheManager: public VPrincipale { // On herite de l'interface et du comportement
    struct Handler
    {
       TacheManager* instance;
       Handler():instance(0){}
       ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
    };
    static Handler handler;
public:
    TacheManager():VPrincipale(){}
    TacheManager(const QString& f):VPrincipale(f){}
    static TacheManager& getInstance();
    static void libererInstance();
    void afficher(QTextStream& f) const
    {
        f<<"****TacheManager*****";
    }
    //void ajouterTache(); //à adapter selon TacheU ou TacheC --> design pattern
    //Tache& getTache(const QString& id);
};

//******************************************************************************************
class Programmation
{
    friend class ProgrammationManager;
    const Event* event;
    Date date;
    Horaire horaire;
    //constructeurs et destructeur en privé car les Programmations sont gérées par ProgrammationManager
    Programmation(const Event& e, const Date& d, const Horaire& h):event(&e), date(d), horaire(h){}
    Programmation(const Programmation& e);
public:
    const Event& getEvent() const { return *event; }
    const Date& getDate() const { return date; }
    const Horaire& getHoraire() const { return horaire; }
};

class ProgrammationManager {
    typedef std::vector<Programmation*> vectProg;
    vectProg progs;
    void addItem(Programmation* t);
    Programmation* trouverProgrammation(const Event& t) const;
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
    ProgrammationManager();
    ~ProgrammationManager();
    ProgrammationManager& getInstance();
    void libererInstance();
    void ajouterProgrammation(const Event& e, const Date& d, const QTime& h);
    //Programmation& getProgrammation(const QString& id_evt);
};

//******************************************************************************************

#endif // CALENDAR_H

