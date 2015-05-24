#ifndef CALENDAR_H
#define CALENDAR_H
#include <QString>
#include <QDate>
#include <QTextStream>
#include <vector>
#include<QUuid>
#include<sstream>
#include "timing.h"
using namespace std;
using namespace TIME;



//******************************************************************************************
class CalendarException
{
    QString info;
public:
    CalendarException(const QString& message):info(message){}
    QString getInfo() const { return info; }
};

QTextStream& operator<<(QTextStream& f, const Duree & d);
QTextStream& operator>>(QTextStream&, Duree&); //lecture format hhHmm

//******************************************************************************************
class Tache {
private:
    QString id;
    QString titre;
    Duree duree;
    QDate disponibilite;
    QDate echeance;
protected:Tache(const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadl):titre(t), duree(dur), disponibilite(dispo), echeance(deadl)
    {
        QUuid u=QUuid::createUuid();
        this->id=u.toString();
    }
    Tache(const Tache& t);
    Tache& operator=(const Tache&);
    friend class TacheManager;
public:
    const QString getId() const { return id; }
    //pas de setId : l'utilisateur n'a pas le droit de modifier l'id : void setId(const QString& str);
    const QString getTitre() const { return titre; }
     void setTitre(const QString& str) { titre = str; }
    const Duree getDuree() const { return duree; }
    virtual void setDuree(const Duree& d) { duree = d; }
    const QDate getDisponibilite() const { return disponibilite; }
    const QDate getEcheance() const { return echeance; }
   inline void setDisponibilite(const QDate& d);
   inline void setEcheance(const QDate& e);
    virtual std::string toString() const=0;
    void afficher(std::ostream& f= std::cout) const
  {
            f<<"**Tache** \n";
            //f<<"Id"<< id <<"Titre "<<titre<<"\n";
            //f<<"Duree "<< duree<<"Disponibilite "<< disponibilite <<"Echeance "<< echeance<<"\n";
            f<<toString();

        }



};

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
    Activite(const QString& t, const Duree d, const QString& l):id(id), titre(t), duree(d), lieu(l)
    {
        QUuid u=QUuid::createUuid();
        this->id=u.toString();
    }
    const QString& getId() const { return id; }
    const QString& getTitre() const { return titre; }
    const Duree& getDuree() const { return duree; }
    const QString& getLieu() const { return lieu; }
    virtual void Afficher_Activite () const =0;
};
class Rdv : public Activite
{
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
    TacheU(const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadline, bool pre=false, bool prog=false):
        Tache(t,dur,dispo,deadline), preemptive(pre), programmee(prog) {
        if ((preemptive == false) && (getDuree().getDureeEnHeures() > 12))
                throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
    }
    TacheU(Tache& t, bool pre=false, bool prog=false):Tache(t.getTitre(),t.getDuree(),t.getDisponibilite(),t.getEcheance()), preemptive(pre), programmee(prog){}
    void setDuree(const Duree& d); //redéfinition
    const bool isPreemptive() const { return preemptive; }
    const bool isProgrammee() const { return programmee; }
    void setPreemptive()
    {
        if(getDuree().getDureeEnHeures() > 12) throw CalendarException ("Duree de la tache inferieur a 12");
        preemptive = true;
}
    void setNonPreemptive() {
        if(getDuree().getDureeEnHeures() > 12)
            throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
        preemptive = false;
    }

    void setProgrammee() { programmee = true; }
    void setNonProgrammee() { programmee = false; }
    std::string toString() const
        {

            std::stringstream f;
            f<<"**Tache Unitaire** \n";
            if(isPreemptive()) f<<"Tache Preemtive \n";
            if(isProgrammee()) f<<"Tache Programmee \n";
            return f.str();
        }

};

class TacheC : public Tache {
    typedef std::vector<Tache *> vectcomp;
    vectcomp tachescomp;
public:
    TacheC(const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadl): Tache(t,dur,dispo,deadl)
    { tachescomp.reserve(10); }
    //bool Precedence(const Tache& t);
    //void ajoutTache(const Tache& t);
    std::string toString() const
        {
            std::stringstream f;
            f<<"**Tache Composite** \n";
            for(vectcomp::const_iterator it= tachescomp.begin(); it!=tachescomp.end();++it)
                    {
                        (*it)->afficher();
                    }
            return f.str();
        }
    ~TacheC() { tachescomp.clear(); } //clear() vide le contenu du conteneur
};

QTextStream& operator<<(QTextStream& f, const Tache& t);

//******************************************************************************************


//******************************************************************************************
class VPrincipale // class abstraite pour le tableau de taches
{
    typedef std::vector<Tache*> tabtaches;
    tabtaches taches;
    QString file;
    unsigned int nb;
    unsigned int nbMax;
  public:
    void addItem(Tache* t);
    Tache* trouverTache(const QString& id) const;
    VPrincipale() { taches.reserve(10); }
    VPrincipale(const QString& f): file(f) { taches.reserve(10); }
    virtual ~VPrincipale();
    VPrincipale(const VPrincipale& m);
    VPrincipale& operator=(const VPrincipale& m);
    TacheU& ajouterTacheU(const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadline, bool preempt=false, bool prog=false);
    Tache& getTache(const QString& id);
    bool isTacheExistante(const QString& id) const { return trouverTache(id)!=0; }
    const Tache& getTache(const QString& code) const;
    void load(const QString& f);
    void save(const QString& f);
    virtual void afficher(QTextStream& f) const =0;

};

//******************************************************************************************
class Projet: public VPrincipale // On herite de l'interface et du comportement
{
    QString id;
    QString titre;
    QDate disponibilite;
    QDate echeance;
    struct Handler
     {
        Projet* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
        };
    static Handler handler;
    Projet(const QString& t,const QDate& disp, const QDate& ech):id(id), titre(t), disponibilite(disp), echeance(ech),VPrincipale()
    {
        QUuid u=QUuid::createUuid();
        this->id=u.toString();
    }

 public:

    static Projet& getInstance();
    static void libererInstance();
    const QString& getId() const { return id; }
    const QString& getTitre() const { return titre; }
    const QDate& getDisponibilite() const { return disponibilite; }
    const QDate& getEcheance() const { return echeance; }
    void setdisponbilite(QDate d) {this->disponibilite=d;}
    void setecheance (QDate e) {this->echeance=e;}
    void afficher(QTextStream& f) const
    {

        f<<"****Projet*****";

    }

};

class ProjetManager: public VPrincipale
{
    typedef std::vector<Projet*> TabProjet;
    TabProjet tabprojets;
    struct Handler
    {
        ProjetManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
    };
    static Handler handler;
public:
    static ProjetManager& getInstance();
    static void libererInstance();
    void afficher(QTextStream& f) const
    {
        f<<"****ProjetManaeger*****";
    }



};

//******************************************************************************************
class TacheManager: public VPrincipale // On herite de l'interface et du comportement
{
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


};

//******************************************************************************************
class Programmation {
    const Event* event;
    QDate date;
    QTime horaire;
public:
    Programmation(const Event& e, const QDate& d, const QTime& h):event(&e), date(d), horaire(h){}
    Programmation(const Programmation& e);
    const Event& getEvent() const { return *event; }
    const QDate getDate() const { return date; }
    const QTime getHoraire() const { return horaire; }
};

class ProgrammationManager
{
    typedef std::vector<Programmation*> vectProg;
    vectProg progs;
    ProgrammationManager& operator=(const ProgrammationManager& e);
     ProgrammationManager(const ProgrammationManager& e);


public:
    ProgrammationManager();
    void ajouterProgrammation(const Event& e, const QDate& d, const QTime& h);
    void addItem(Programmation* t);
    Programmation* trouverProgrammation(const Event& t) const;
    ~ProgrammationManager();



};

//******************************************************************************************

#endif // CALENDAR_H

