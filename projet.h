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
    struct Handler
    {
        Projet* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
    };
    //attributs
    tabtaches tachesprojet; //ensemble des tâches
    QString id;
    QString titre;
    Date disponibilite;
    Date echeance;
    static Handler handler;
    //méthodes
    Projet(const QString& t,const Date& disp, const Date& ech):titre(t), disponibilite(disp), echeance(ech)
    { QUuid u=QUuid::createUuid(); this->id=u.toString(); tachesprojet.reserve(10); }
    Projet(const Projet& m);
    Projet& operator=(const Projet& m);
    ~Projet();
    void addTache(Tache* t) { tachesprojet.push_back(t); }
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
    void load(const QString& f);
    void save(const QString& f);
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
    void addProjet(Projet* p);
public:
    static ProjetManager& getInstance();
    static void libererInstance();
    void creerProjet(const QString& t,const Date& disp, const Date& ech); // crée le projet et le renvoie à addprojet pour l'ajouter
    void afficher(QTextStream& f) const { f<<"****ProjetManager*****";}
    void load(const QString& f);
    void save(const QString& f);
    Projet& getProjet(const QString& id);
    void ajouterTacheAProjet(Projet& p, Tache* t);
};

//******************************************************************************************

#endif // PROJET_H

