#ifndef CALENDAR_H
#define CALENDAR_H
#include <QString>
#include <QDate>
#include <QTextStream>
#include "timing.h"
using namespace std;

QTextStream& operator<<(QTextStream& f, const Duree & d);
QTextStream& operator>>(QTextStream&, Duree&); //lecture format hhHmm

class Tache
{
 private:
    QString identificateur;
    QString titre;
    Duree duree;
    QDate disponibilite;
    QDate echeance;
protected: Tache(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadl, bool preempt=false):
            identificateur(id),titre(t),duree(dur),disponibilite(dispo),echeance(deadl){}
    Tache(const Tache& t);
    Tache& operator=(const Tache&);
    friend class TacheManager;
public:
    QString getId() const { return identificateur; }
    void setId(const QString& str);
    QString getTitre() const { return titre; }
    void setTitre(const QString& str) { titre=str; }
    Duree getDuree() const { return duree; }
    void setDuree(const Duree& d) { duree=d; }
    QDate getDateDisponibilite() const {  return disponibilite; }
    QDate getDateEcheance() const {  return echeance; }
    void setDatesDisponibiliteEcheance(const QDate& disp, const QDate& e)
    {
        if (e<disp) throw CalendarException("erreur Tache : date echeance < date disponibilite");
        disponibilite=disp; echeance=e;

    }
    virtual void Afficher_Tache () const =0;

};

//******************************************************************************************
class Event // CLASSE ABSTRAITE
{

public:
};


class Activite: public Event
{
    QString type;
public:

};

//******************************************************************************************
class TacheU : protected Tache , public Event
{
    bool preemptive;
    TacheU(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadline, bool p=false):
        Tache(id,t,dur,dispo,deadline), preemptive(p){}
    TacheU(Tache& t, bool p=false):Tache(t.getId(),t.getTitre(),t.getDuree(),t.getDateDisponibilite(),t.getDateEcheance()),preemptive(p){}
 public:
    bool isPreemptive() const { return preemptive; }
    void setPreemptive() { preemptive=true; }
    void setNonPreemptive() { preemptive=false; }
    void Afficher_Tache() const ;

};


class TacheC : public Tache
{
    Tache* tache_C;

public:
    //TacheC(): tache_C(){}

};

QTextStream& operator<<(QTextStream& f, const Tache& t);

//******************************************************************************************
class Projet
{
    QString intitule;
    Tache** taches;
    QDate disponibilite;
    QDate echeance;
 public:
    Projet(const QString& s,const Tache& t, const QDate& disp, const QDate& ech):Tache(&t),intitule(s), disponibilite(disp), echeance(ech){}
    QDate getdisponibilite() const { return disponibilite; }
    QDate getecheance() const { return echeance;}
    void setdisponbilite(QDate d) {this->disponibilite=d;}
    void setecheance (QDate e) {this->echeance=e;}


    class iterator
    {
        Tache** current;
        iterator(Tache** u):current(u){}
        friend class TacheManager;
    public:
        iterator():current(0){}
        Tache& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(taches); }
    iterator end() { return iterator(taches+nb); }
};

//******************************************************************************************
class TacheManager
{
private:
    Tache** taches;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(Tache* t);
    Tache* trouverTache(const QString& id) const;
    QString file;
    TacheManager();
    ~TacheManager();
    TacheManager(const TacheManager& um);
    TacheManager& operator=(const TacheManager& um);
    struct Handler
    {
        TacheManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
    };
    static Handler handler;
public:
    Tache& ajouterTache(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadline, bool preempt=false);
    Tache& getTache(const QString& id);
    bool isTacheExistante(const QString& id) const { return trouverTache(id)!=0; }
    const Tache& getTache(const QString& code) const;
    void load(const QString& f);
    void save(const QString& f);
    static TacheManager& getInstance();
    static void libererInstance();

    class Iterator
    {
        friend class TacheManager;
        Tache** currentTache;
        unsigned int nbRemain;
        Iterator(Tache** u, unsigned nb):currentTache(u),nbRemain(nb){}
    public:
        Iterator():nbRemain(0),currentTache(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw CalendarException("error, next on an iterator which is done");
            nbRemain--;
            currentTache++;
        }
        Tache& current() const {
            if (isDone())
                throw CalendarException("error, indirection on an iterator which is done");
            return **currentTache;
        }
    };
    Iterator getIterator()
    {
        return Iterator(taches,nb);
    }


    class ConstIterator
    {
        friend class TacheManager;
        Tache** currentTache;
        unsigned int nbRemain;
        ConstIterator(Tache** u, unsigned nb):currentTache(u),nbRemain(nb){}
    public:
        ConstIterator():nbRemain(0),currentTache(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw CalendarException("error, next on an iterator which is done");
            nbRemain--;
            currentTache++;
        }
        const Tache& current() const {
            if (isDone())
                throw CalendarException("error, indirection on an iterator which is done");
            return **currentTache;
        }
    };
    ConstIterator getIterator() const
    {
        return ConstIterator(taches,nb);
    }

    class iterator
    {
        Tache** current;
        iterator(Tache** u):current(u){}
        friend class TacheManager;
    public:
        iterator():current(0){}
        Tache& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(taches); }
    iterator end() { return iterator(taches+nb); }

    class const_iterator
    {
        Tache** current;
        const_iterator(Tache** u):current(u){}
        friend class TacheManager;
    public:
        const_iterator():current(0){};
        Tache& operator*() const { return **current; }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ ++current; return *this; }
    };

    const_iterator begin() const { return const_iterator(taches); }
    const_iterator end() const { return const_iterator(taches+nb); }

    class DisponibiliteFilterIterator
    {
        friend class TacheManager;
        Tache** currentTache;
        unsigned int nbRemain;
        QDate dispo;
        DisponibiliteFilterIterator(Tache** u, unsigned nb, const QDate& d):currentTache(u),nbRemain(nb),dispo(d)
        {
            while(nbRemain>0 && dispo<(*currentTache)->getDateDisponibilite()){
                nbRemain--; currentTache++;
            }
        }
    public:
        DisponibiliteFilterIterator():nbRemain(0),currentTache(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw CalendarException("error, next on an iterator which is done");
            do {
                nbRemain--; currentTache++;
                }
            while(nbRemain>0 && dispo<(*currentTache)->getDateDisponibilite());
        }
        Tache& current() const
        {
            if (isDone())
                throw CalendarException("error, indirection on an iterator which is done");
            return **currentTache;
        }
    };
    DisponibiliteFilterIterator getDisponibiliteFilterIterator(const QDate& d)
    {
        return DisponibiliteFilterIterator(taches,nb,d);
    }
};


//******************************************************************************************


class Programmation
{
    const Event* events;
    QDate date;
    QTime horaire;
public:
    Programmation(const Event& e, const QDate& d, const QTime& h):events(&e), date(d), horaire(h){}
    const Event& getEvent() const { return *events; }
    QDate getDate() const { return date; }
    QTime getHoraire() const { return horaire; }
};

class ProgrammationManager
{
private:
    Programmation** programmations;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(Programmation* t);
    Programmation* trouverProgrammation(const Event& t) const;
public:
    ProgrammationManager();
    ~ProgrammationManager();
    ProgrammationManager(const ProgrammationManager& e);
    ProgrammationManager& operator=(const ProgrammationManager& e);
    void ajouterProgrammation(const Event& e, const QDate& d, const QTime& h);
};

//******************************************************************************************



#endif // CALENDAR_H

