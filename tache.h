#ifndef TACHE_H
#define TACHE_H
#include <QString>
#include <QTextStream>
#include <vector>
#include <QUuid>
#include <sstream>
#include <typeinfo>
#include "calendar.h"
#include "evenement.h"
#include<algorithm>

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

    //méthodes
    Tache(const Tache& t); //pas implémentée: on ne devrait pas l'implementer car chaque tache unique -->id
    Tache& operator=(const Tache&); //pas implémentée:on ne devrait pas l'implementer car chaque tache unique -->id
    //les méthodes set sont privées car c'est TacheManager qui gère les Tache
protected:
    Tache(const QString& id, const QString& t, const Duree& dur, const Date& dispo, const Date& deadl): id(id), titre(t),duree(dur),disponibilite(dispo),echeance(deadl){}
    virtual ~Tache(){};
    virtual void setDuree(const Duree& d) { duree = d; }
    void setId(const QString& str);
    void setTitre(const QString& str) { titre = str; }
    inline void setDisponibilite(const Date& d);
    inline void setEcheance(const Date& e);
public:
    virtual const QString& getId() const { return id; }
    virtual const QString& getTitre() const { return titre; }
    virtual const Duree& getDuree() const { return duree; }
    const Date getDisponibilite() const { return disponibilite; }
    const Date getEcheance() const { return echeance;}
    virtual const QString toString() const=0;
    virtual bool getTypeTache()=0; /*! \fn * fonction retounant vrai si la tache est unitaire
                                           * Elle nous permettera de verifier que la tache est unitaire pour la programmer ou y ajouter des précédences.
                                           */
};

QTextStream& operator<<(QTextStream& fout, const Tache* const t);

//******************************************************************************************

class TacheU : public Tache , public Event {
    /*! \class TacheU
     \brief Classe héritant de Tache permettant de manipuler des tâches unitaires
     \param progression >0 et <100 : permettant de suivre la progression des taches preemtives après leur programmation, puisqu'on peut programmer une tache preemtive à plusieurs reprises
     \param precedence est un vector contenant toutes les taches qui précèdent la tache
     \param suivante est vector contenant toutes les taches qui viennent après la tache
    */
    friend class TacheManager;
    typedef vector<TacheU*> tabtachesU;
     /*!  \typedef  tabtachesU est un vecteur de Taches Unitaires*/
    //attributs
    bool preemptive;
    unsigned int progression;

    tabtachesU precedence;
    tabtachesU suivante;//

    //méthodes
    void setDuree(const Duree& d);
    void setPreemptive() { preemptive = true;}
    inline void setNonPreemptive();
protected:
    TacheU(const QString& id, const QString& t, const Duree& dur, const Date& dispo, const Date& deadline, const bool& pre=false, const bool& prog=false):
    Tache(id,t,dur,dispo,deadline), Event(prog), preemptive(pre), progression(0)
    {
        if ((preemptive == false) && (dur.getDureeEnHeures() > 12))
        throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
        precedence.reserve(5);
        suivante.reserve(5);
    }  //! Constructeur à partir de minute

    TacheU(const Tache& t, const bool& pre=false, const bool& prog=false): /*! \param programmation false */
    Tache(t.getId(), t.getTitre(),t.getDuree(),t.getDisponibilite(),t.getEcheance()), Event(prog), preemptive(pre),progression(0) {}
public:
    void ajouterPrecedence(TacheU* t );
    void supprimerPrecedence(const QString& id);
    tabtachesU& getPrecedence(){ return precedence;}
    tabtachesU& getSuivante(){ return suivante;}
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
    bool getTypeTache(){ return true;}
    const QString toString() const;
};

//******************************************************************************************

class TacheC : public Tache {
    /*! \class TacheC
     \brief Classe héritant de Tache permettant de manipuler des tâches composites
     */
    friend class TacheManager;
    typedef std::vector<Tache *> tabtaches;
    /*!  \typedef  tabtaches est un vecteur de Taches*/
    //attributs
    tabtaches tachescomp;
    //méthodes
    ~TacheC() { tachescomp.clear(); } //clear() vide le contenu du conteneur
    TacheC(const QString& id, const QString& t, const Duree& dur, const Date& dispo, const Date& deadl): Tache(id,t,dur,dispo,deadl)
    { tachescomp.reserve(10); }
     void addTasktoC(Tache* );
public:
    const QString toString() const;
    tabtaches& getCTaches(){return tachescomp;}
   bool getTypeTache(){ return false;}
};

//******************************************************************************************

class TacheManager
{
    /*! \class TacheManager
     \brief Classe permettant de créer, modifier et détruire des tâches
     */
    friend class NewProject;
    typedef std::vector<Tache*> tabtaches;
    /*!  \typedef  tabtaches est un vecteur de Taches */
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
    TacheManager(const TacheManager&);
    TacheManager& operator=(const TacheManager&);
    template <class T> void addItem(T* t) { taches.push_back(t); }
public:
    static TacheManager& getInstance(); //!< Donne l'instance unique de TacheManager
    static void libererInstance(); //!< Libère l'instance unique de TacheManager
    tabtaches& getTabTaches() { return taches; }
    TacheU* ajouterTacheU(const QString &id, const QString& t, const Duree& dur, const Date& dispo, const Date& deadline, const bool& preempt=false, const bool& prog=false);
    //! Construction d'une tache Unitaire en faisant appel au constructeur de Tache Unitaire
    TacheC* ajouterTacheC(const QString& id, const QString& t, const Duree& dur, const Date& dispo, const Date& deadl);
    //! Construction d'une tache Composite en faisant appel au constructeur de Tache Composite
   void ajouter_Tache_a_composite(TacheC* ,Tache* );
   void load(const QString& ); //! Chager un fichier xml contenant des taches
   void save(const QString& );
   void afficher(QTextStream& f) const { f << "****TacheManager*****" << endl; }
   Tache* getTache(const QString&);
   TacheU* getTacheU(const QString&); // ne retourne que les taches Unitaires pour pouvoir les programmer
   void ajouterPrecedenceTache(TacheU*,TacheU*);
   void remove_Task(const QString& id)
    {
        Tache* todelete=getTache(id);
        tabtaches::iterator position = std::find(taches.begin(), taches.end(), todelete);
        if (position != taches.end()) // == vector.end() means the element was not found
            taches.erase(position);

        }
    QTextStream& afficherTaches(QTextStream& fout);
    const QString& afficherTachesAProgrammer() const;//! Affiche les Taches qui ne sont pas programmées

};

//******************************************************************************************

#endif // TACHE_H

