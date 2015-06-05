#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QTextStream>
#include <vector>
#include <QUuid>
#include <sstream>
#include "timing.h"
#include "calendar.h"
#include "tache.h"

using namespace std;
using namespace TIME;

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

#endif // PROJET_H

