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
class CalendarException
{
    QString info;
public:
    CalendarException(const QString& message) : info(message) {}
    QString getInfo() const { return info; }
};

//******************************************************************************************
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
class Event  // CLASSE ABSTRAITE
{

 public:
};

class Activite: public Event
{
    QString id;
    QString titre;
    Duree duree;
    QString lieu;
public:
    Activite(const QString& t, const Duree d, const QString& l):id(id), titre(t), duree(d), lieu(l) {
        QUuid u=QUuid::createUuid(); this->id=u.toString(); }
    const QString& getId() const { return id; }
    const QString& getTitre() const { return titre; }
    void setTitre(const QString& t ) { this->titre=t; }
    const Duree& getDuree() const { return duree; }
    void setDuree(const Duree& d) { this->duree=d; }
    const QString& getLieu() const { return lieu; }
    QString& setLieu(const QString& l) { this->lieu =l; }
    virtual void Afficher_Activite () const =0;
};

class Rdv : public Activite
{
    QString personne;
public:
    Rdv(const QString& t, const Duree d, const QString& l, const QString& p):Activite(t,d,l), personne(p) {}
};

class Reunion : public Activite
{
    QString outils;
public:
    Reunion(const QString& t, const Duree d, const QString& l, const QString& o):Activite(t,d,l),outils(o){}
};

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
//******************************************************************************************
class Projet
{
    friend class ProjetManager;
    typedef std::vector<Tache*> tabtaches;
    tabtaches tachesprojet;
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
    Projet(const QString& t,const Date& disp, const Date& ech):titre(t), disponibilite(disp), echeance(ech)
    { QUuid u=QUuid::createUuid(); this->id=u.toString(); }
    Projet(const Projet& m);
    Projet& operator=(const Projet& m);
     ~Projet();
public:
    static Projet& getInstance();
    static void libererInstance();
    const QString& getId() const { return id; }
    const QString& getTitre() const { return titre; }
    const Date& getDisponibilite() const { return disponibilite; }
    const Date& getEcheance() const { return echeance; }
    void setDisponbilite(Date d) { this->disponibilite=d; }
    void setEcheance (Date e) { this->echeance=e; }
    const Tache& getTache(const QString& code) const;
    template <class T> void addTache(T* t)
    {
       tachesprojet.push_back(t);
    }
    void load(const QString& f);
    void save(const QString& f);
     void afficher(QTextStream& f) const {f<<"****Projet*****";}

};

//******************************************************************************************
class ProjetManager{
    //>>>>>>> Stashed changes
    typedef std::vector<Projet*> TabProjet;
    TabProjet tabprojets;
    QString file;
    struct Handler {
        ProjetManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
    };
    static Handler handler;
    ProjetManager(const ProjetManager& m);
    ProjetManager& operator=(const ProjetManager& m);

public:
    ProjetManager() { tabprojets.reserve(10);}
    static ProjetManager& getInstance();
    static void libererInstance();
    void ajouterProjet(const QString& t,const Date& disp, const Date& ech); // cree le projet et le renvoie a addprojet pour l'ajouter
    void addprojet(Projet* p);
    void afficher(QTextStream& f) const { f<<"****ProjetManaeger*****";}
    void load(const QString& f);
    void save(const QString& f);

    //Projet& getProjet(const QString& id);
};

//******************************************************************************************
//******************************************************************************************
class ProgrammationManager;

class Programmation
{
    friend ProgrammationManager;
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
    ProgrammationManager& getInstance();
    void libererInstance();
    Programmation* trouverProgrammation(const Event& t) const;
    Programmation& getProg(const QString& id_evt);
    void ajouterProgrammation (const Event& e, const Date& d, const Horaire& h);
    void addprog(Programmation* p);
};

//******************************************************************************************

#endif // CALENDAR_H

