#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include <QTextStream>
#include <vector>
#include <QUuid>
#include <sstream>
#include "calendar.h"

using namespace TIME;

class Event  // CLASSE ABSTRAITE
{
    /*! \class Event
            \brief Classe permettant de créer des événements
            Un objet Event est soit un objet Tache, soit un objet Activite
    */
    bool programmee; //!<attribut programmee vaut TRUE si Event est programmé, FALSE sinon
    
public:
    Event(const bool& p=false):programmee(p){}
    bool estProgrammee() const { return programmee; }
    void setProgrammee() { programmee = true; }
    void setNonProgrammee() { programmee = false; }
    virtual bool cestunetache() const =0;/*! pour savoir si l'evenement est une tache Unitaire ou un Evenement */
    virtual const QString& getId() const=0;
    virtual const Duree& getDuree() const=0;
    virtual const QString& getTitre() const=0;
    virtual const QString toString() const=0;
};

class Activite: public Event
{
    /*! \class Activite
            \brief Classe permettant de créer des activités
            Un objet Activite est soit un objet Rdv, soit un objet Reunion
    */
    QString id;
    QString titre;
    Duree duree;
    QString lieu;
public:
    Activite(const QString& i, const QString& t, const Duree d, const QString& l="UTC"):id(i), titre(t), duree(d), lieu(l) {}
    const QString& getId() const { return id; }
    const QString& getTitre() const { return titre; }
    void setTitre(const QString& t ) { this->titre=t; }
    const Duree& getDuree() const { return duree; }
    void setDuree(const Duree& d) { this->duree=d; }
    const QString& getLieu() const { return lieu; }
    void setLieu(const QString& l) { this->lieu =l; }
    virtual void Afficher_Activite () const =0;
    bool  cestunetache() const { return false; }
    const QString toString() const;
    virtual bool estUnRdv() const=0;
};

class Rdv : public Activite
{
    /*! \class Rdv
            \brief Classe permettant de créer des rendez-vous
            Elle hérite de Activite
    */
    QString personne;
public:
    Rdv(const QString& i, const QString& t, const Duree d, const QString& l, const QString& p):Activite(i,t,d,l), personne(p) {}
    void Afficher_Activite () const;
    bool estUnRdv() const { return true; }
};

class Reunion : public Activite
{
    /*! \class Reunion
            \brief Classe permettant de créer des réunion
            Elle hérite de Activite
    */
public:
    Reunion(const QString& i, const QString& t, const Duree d, const QString& l):Activite(i,t,d,l){}
    void Afficher_Activite () const;
    bool estUnRdv() const { return false; }
};

//******************************************************************************************


#endif // EVENEMENT_H

