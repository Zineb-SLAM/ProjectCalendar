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
    typedef std::vector<Tache*> tabtaches; //vecteur de la STL contenant des pointeurs sur des objets Tache
    //attributs
    QString id;
    QString titre;
    Date disponibilite;
    Date echeance;
    bool termine; // si termine == TRUE, cela signifie que le projet est terminé (toutes les tâches ont été réalisées)
    tabtaches tachesProjet; //ensemble des tâches du projet
    //méthodes
    Projet(const QString& id, const QString& t, const Date& disp, const Date& ech):id(id), titre(t), disponibilite(disp), echeance(ech), termine(false){}
    void setTermine() { termine = true; }
    void setDisponbilite(Date d) { this->disponibilite=d; }
    void setEcheance (Date e) { this->echeance=e; }
    void addTache(Tache* t);
    void removetache(Tache*t);
    Projet(const Projet& m);
    Projet& operator=(const Projet& m);
    ~Projet();
    
public:
    const QString& getId() const { return id; }
    const QString& getTitre() const { return titre; }
    const Date& getDisponibilite() const { return disponibilite; }
    const Date& getEcheance() const { return echeance; }
    const bool& isTermine() const { return termine; }
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
    bool ProjetExists(const Projet* const p);
    Projet* getProjet(const QString& id);
    void removeProject(Projet* p);
    void creerProjet(const QString &id, const QString& t, const Date& disp, const Date& ech); // crée le projet et l'ajoute à la liste des projets existants
    void ajouterTacheAProjet(Projet& p, Tache* t);
    void afficher(QTextStream& f) const { f<<"****ProjetManager*****"; }
    void load(const QString& f);
    void save(const QString& f);
};

//******************************************************************************************

#endif // PROJET_H

