#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QTextStream>
#include <vector>
#include <QUuid>
#include <sstream>
#include "calendar.h"
#include "tache.h"

using namespace std;
using namespace TIME;

class Projet {
    /*! \class Projet
     \brief Classe permettant de manipuler des projets
     */
    friend class ProjetManager;
    typedef std::vector<Tache*> tabtaches;
    //attributs
    tabtaches tachesprojet; //ensemble des tâches
    QString id;
    QString titre;
    Date disponibilite;
    Date echeance;
    bool isCompleted; // ajout de completed
    //méthodes
    Projet(const QString& t,const Date& disp, const Date& ech):titre(t), disponibilite(disp), echeance(ech),isCompleted(false)
    {
        QUuid u=QUuid::createUuid(); this->id=u.toString();
        tachesprojet.reserve(10);
    }
    void setCompleted() {isCompleted = true;}
    void addTache(Tache* t) {
        if(Taskunavalaible(t))
        throw CalendarException ("La tache appartient deja au projet");
        tachesprojet.push_back(t); }
    void removetache(Tache*t);
    Projet(const Projet& m);
    Projet& operator=(const Projet& m);
    ~Projet();
    
public:
    const QString& getId() const { return id; }
    const QString& getTitre() const { return titre; }
    const Date& getDisponibilite() const { return disponibilite; }
    const Date& getEcheance() const { return echeance; }
    void setDisponbilite(Date d) { this->disponibilite=d; }
    void setEcheance (Date e) { this->echeance=e; }
    const Tache& getTache(const QString& code) const;
    bool Taskunavalaible(Tache* t);
    void afficher(QTextStream& f) const {f<<"****Projet*****";}
};

//******************************************************************************************
class ProjetManager{
    /*! \class ProjetManager
     \brief Classe permettant de créer, modifier et détruire des projets
     */
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
    ProjetManager() { tabprojets.reserve(10);}
public:
    static ProjetManager& getInstance();
    static void libererInstance();
    bool Projetexists(const Projet* const p);
    Projet* getProjet(const QString& id);
    void removeProject(Projet* p);
    void creerProjet(const QString& t,const Date& disp, const Date& ech); // crée le projet et le renvoie à addprojet pour l'ajouter
    void addProjet(Projet* p);
    void ajouterTacheAProjet(Projet& p, Tache* t);
    void afficher(QTextStream& f) const { f<<"****ProjetManager*****";}
    void load(const QString& f);
    void save(const QString& f);
};

//******************************************************************************************

#endif // PROJET_H

