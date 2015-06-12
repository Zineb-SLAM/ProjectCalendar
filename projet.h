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
    //amitiés
    friend class ProjetManager;
    //structures
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
    void setId(const QString& identifiant) { id = identifiant; }
    void setTermine() { termine = true; }
    void setDisponbilite(const Date& d) { disponibilite = d; }
    void setEcheance (const Date& e) { echeance = e; }
    void addTache(Tache* t);
    void removeTache(Tache*t);
    Projet(const Projet& m);
    Projet& operator=(const Projet& m);
    ~Projet();
public:
    const QString& getId() const { return id; }
    const QString& getTitre() const { return titre; }
    const Date& getDisponibilite() const { return disponibilite; }
    const Date& getEcheance() const { return echeance; }
    tabtaches& GetTabProjet(){ return tachesProjet;}
    const bool& isTermine() const { return termine; }
    const Tache* getTache(const QString& id) const;
    bool isTacheDansProjet(Tache* t);
    void afficher(QTextStream& f) const;
};

//******************************************************************************************
class ProjetManager{
    /*! \class ProjetManager
            \brief Classe permettant de créer, modifier et détruire des projets
    */
    //structures
    typedef std::vector<Projet*> tabprojets;
    struct Handler {
        ProjetManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; } // destructeur appel a la fin du programme
    };
    //attributs
    tabprojets projets;
    QString file;
    static Handler handler;
    //méthodes
    ProjetManager(const ProjetManager& m);
    ProjetManager& operator=(const ProjetManager& m);
    ProjetManager() { projets.reserve(10); }
    ~ProjetManager() { projets.clear(); }
public:
    static ProjetManager& getInstance();
    static void libererInstance();
    bool ProjetExists(const QString& id); // retourne TRUE si le projet existe déjà
    Projet* getProjet(const QString& id);
    std::vector<Projet*>& getTab(){return projets;}
    void creerProjet(const QString &id, const QString& t, const Date& disp, const Date& ech); // crée le projet et l'ajoute à la liste des projets existants
    void ajouterTacheAProjet(Projet*  p, Tache* t);
    void removeProject(const QString& id);
    void afficher(QTextStream& f) const { f<<"****ProjetManager*****"; }
    void load(const QString& f);
    void save(const QString& f);
    void afficherTitreProjets(QTextStream& fout) const; // affiche le titre de tous les projets existants
    void afficherProjets(QTextStream& fout) const;
    const QString& afficherTitreProjets() const;
};

//******************************************************************************************

#endif // PROJET_H

