#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H

#include <QString>
#include <QTextStream>
#include <vector>
#include <QUuid>
#include <sstream>
#include "calendar.h"
#include "evenement.h"
#include "tache.h"

using namespace std;
using namespace TIME;

class Programmation
        /*! \class Programmation
                \brief Classe permettant de programmer un evenement avec un date et un horaire
        */
{
    //amitiés
    friend class ProgrammationManager;
    //attributs
    const Event* event;
    Date date;
    Horaire horaire;
    /*! constructeurs et destructeur en privé car les Programmations sont gérées par ProgrammationManager */
    Programmation(const Event* e, const Date& d, const Horaire& h):event(e), date(d), horaire(h){}
    Programmation(const Programmation& e);
public:
    const Event* getEvent() const { return event; }
    const Date& getDate() const { return date; }
    const Date& getDate()  { return date; }
    const Horaire& getHoraire() { return horaire; }
    const Horaire& getHoraire() const { return horaire;}
    QTextStream& afficher(QTextStream& f)const ;
};
QTextStream& operator<<(QTextStream& fout, const Programmation* t);

//******************************************************************************************

class ProgrammationManager
{
    /*! \class ProgrammationManager
            \brief Classe contenant toutes les programmations des evenemnts , cette classe
            gère la création et la destructions des programmations des Evenements
    */

    typedef std::vector<Programmation*> vectProg;
    /*!  \typedef  VectProg est un vecteur de Programmations*/
    vectProg tabprogs;
    ProgrammationManager(const ProgrammationManager& e);//!< Methode Privé: ProgrammationManager etant un singelton, il faut empecher la construction par recopie d'un autre objet ProgrammationManager
    ProgrammationManager& operator=(const ProgrammationManager& e);//!<Operateur Privé: ProgrammationManager etant un singelton, il faut empecher la construction d'un autre objet ProgrammationManager par le biais de l'operateur =
    struct Handler
    {
        ProgrammationManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; } /*! L'avantage destructeur avec Handler est que le destructeur sera appelé automatiquement à la fin du programme */
    };
    static Handler handler;
public:
    ProgrammationManager(){ tabprogs.reserve(10);};
    ~ProgrammationManager();
    static ProgrammationManager& getInstance();
    static void libererInstance();
    vectProg& getTabprogs() { return tabprogs; } //!< Retourne le Tableau de Programmation
    Programmation* trouverProgrammation(const Event* t); //!< Retourne La Programmation de l'Evenement passé en paramètre
    /*! Appel du Constructeur de Programmation*/
    void ajouterProgrammation(TacheU* t, const Date& d, const Horaire& h);
    /*! \fn  Creer la Programmation de Tache Unitaire en ajoutant la date et l'horaire*/
    void ajouterProgrammation(TacheU* t, const Date& d, const Horaire& h, const Duree& nb);
     /*! \fn  Creer la Programmation d'une \b Partie seulement d'une tache Unitaire \b Preemtive
        \param Duree& nb va peremttre de suivre  la progression d'une Tache*/
    void ajouterProgrammation(Activite* a, const Date& d, const Horaire& h);
    /*! Programme l'objet Tache Unitaire/Evenement en Créant l'objet Programmation
     * correspondant et rennvoie cet objet à la méthode addprog */
    void addprog(Programmation* p); //!< Methode Appelee par ajouterProgrammation qui ajoute la programmation d'un Evenement au Vector de ProgrammationManager
   //!< Retourne la programmation d'un Evenement ) partir de son Id.
   Programmation* getProg(const QString& id_evt);
    void remove_programmation(const QString& id); /*! \fn Comme on peut avoir une tache unitaire et une activité de même id on verifiera dans la fonction que c'est une activité */
    QTextStream& afficher(QTextStream& f,const Event* t)
    {
       Programmation* a= trouverProgrammation(t);
      return a->afficher(f);
    }

};



//******************************************************************************************

#endif // PROGRAMMATION_H

