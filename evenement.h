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
    bool programmee;
    
public:
    Event(const bool& p=false):programmee(p){}
    bool estProgrammee() const { return programmee; }
    void setProgrammee() { programmee = true; }
    void setNonProgrammee() { programmee = false; }
    virtual bool cestunetache() const =0;
    virtual const QString& getId() const=0;
    virtual const Duree& getDuree() const=0;
    virtual const QString& getTitre() const=0;
    virtual const QString toString() const=0;
};

class Activite: public Event
{
    QString id;
    QString titre;
    Duree duree;
    QString lieu;
public:
    Activite(const QString& i, const QString& t, const Duree d, const QString& l):id(i), titre(t), duree(d), lieu(l) {}
    const QString& getId() const { return id; }
    const QString& getTitre() const { return titre; }
    void setTitre(const QString& t ) { this->titre=t; }
    const Duree& getDuree() const { return duree; }
    void setDuree(const Duree& d) { this->duree=d; }
    const QString& getLieu() const { return lieu; }
    void setLieu(const QString& l) { this->lieu =l; }
    //virtual void Afficher_Activite () const =0;
    bool  cestunetache() const { return false; }
    const QString toString() const;
};

class Rdv : public Activite
{
    QString personne;
public:
    Rdv(const QString& i, const QString& t, const Duree d, const QString& l, const QString& p):Activite(i,t,d,l), personne(p) {}

};

class Reunion : public Activite
{
    //QString outils;
public:
    Reunion(const QString& i, const QString& t, const Duree d, const QString& l/*, const QString& o*/):Activite(i,t,d,l)/*,outils(o)*/{}
};

//******************************************************************************************


#endif // EVENEMENT_H

