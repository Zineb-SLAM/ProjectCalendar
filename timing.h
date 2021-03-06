#ifndef TIMING_H
#define TIMING_H

#include <iostream>
#include <iomanip>
#include <QTextStream>
#include <QString>
#include <cmath>
#include <QDate>

namespace TIME {
    /*! \class TimeException
            \brief Classe permettant de gérer les exceptions des classes du namespace TIME
    */
    class TimeException{
         QString info;
    public:
        //! Constructeur à partir d'une string
        TimeException(const QString& m) : info(m) {}
        const QString& GetInfo() const { return info; } //<! Retourne l'information stockée dans la classe
    };

//******************************************************************************************
    /*! \class Date
            \brief Classe permettant de manipuler des dates standards
            L'utilisation de cette classe nécessite des dates valides au sens commun du terme.
            Déclenchement d'exception dans le cas contraire
    */
    class Date {
        // attributs
        unsigned short int jour; // jour entre 1 et 31
        unsigned short int mois; // mois entre 1 et 12
        unsigned int annee;
    public:
        //! Constructeur à partir d'un jour, mois, année
        /*! \param j jour avec 1<=j<=31
            \param m mois avec 1<=m<=12
            \param a année avec a>=0
            */
        Date(unsigned int short j=1, unsigned int short m=1, unsigned int a=0):jour(1),mois(1),annee(0){ setDate(j,m,a); }
        // méthodes
        unsigned short int getJour() const { return jour; } //<! Retourne le jour de la date
        unsigned short int getMois() const { return mois; } //<! Retourne le mois de la date
        unsigned int getAnnee() const { return annee; } //<! Retourne l'année de la date
        void setDate(unsigned short int j, unsigned short int m, unsigned int a); //!< initialisation de la date
        void setDateAujourdhui(); //!< initialisation de la date avec la date d'aujourd'hui
        void afficher(QTextStream& f) const; //!< affiche le date sous le format JJ/MM/AAAA
        bool operator==(const Date& d) const; //<! d1==d2 retourne vrai si les deux dates sont égales
        bool operator<(const Date& d) const; //<! Compare deux dates dans le temps : d1<d2 retourne true si d1 est avant d2
        int operator-(const Date& d) const; //<! Retourne le nombre de jours séparant les deux dates
        Date demain() const; //<! Retourne la date du lendemain
        Date operator+(unsigned int nb) const; //<!Retourne la date de dans nb jours
        static Date fromString(QString s);
        static QString toString();
        QString& String() const;
        const QDate& toQDate() const;//!< convertit l'objet Date en QDate pour pouvoir utiliser ses fonctions.
    };

//******************************************************************************************
    /*! \class Duree
            \brief Classe permettant de manipuler des durees
            L'utilisation de cette classe néc
essite des dates valides au sens commun du terme.
            Déclenchement d'exception dans le cas contraire
    */
    class Duree{
        unsigned int nb_minutes;
    public:
        //! Constructeur à partir de heure et minute
        /*! \param h heure avec h>=0
            \param m minute avec 0<=m<=59
            */
        Duree(unsigned int h, unsigned int m):nb_minutes(h*60+m) {if (m>59) throw TimeException("erreur: initialisation duree invalide");}
        //! Constructeur à partir de minute
        /*! \param m minute avec m>=0
            */
        Duree(unsigned int m=0):nb_minutes(m) {}
        void setDuree(unsigned int minutes) { nb_minutes=minutes; }
        void setDuree(unsigned int heures, unsigned int minutes) { if (minutes>59) throw TimeException("erreur: initialisation duree invalide"); nb_minutes=heures*60+minutes; }
        unsigned int getDureeEnMinutes() const { return nb_minutes; }  /*! Retourne la duree en minutes */
        double getDureeEnHeures() const { return double(nb_minutes)/60; }  /*! Retourne la duree en heures */
        unsigned int getMinute() const { return nb_minutes%60; }
        unsigned int getHeure() const { return nb_minutes/60; }
        unsigned int getJour() const{ double x = getHeure()/24; return floor(x); } /*! Retourne la duree en jours pour les taches prremptv*/
        void afficher(QTextStream& f) const;  /*! Affiche la duree sous le format hhHmm */
        QString& toString() const;
        static Duree& fromString(const QString &str);
    };


    QTextStream& operator<<(QTextStream& f, const Duree& d);
    QTextStream& operator>>(QTextStream& flot, Duree& duree);  /*! lecture format hhHmm */

//******************************************************************************************
    /*! \class Horaire
            \brief Classe permettant de manipuler des horaires
            L'utilisation de cette classe nécessite des dates valides au sens commun du terme.
            Déclenchement d'exception dans le cas contraire
    */
    class Horaire{
    public:
        //! Constructeur à partir de heure et minute
        /*! \param h heure avec 0<=h<=23
            \param m minute avec 0<=m<=59
            */
        Horaire(unsigned short int  h=0, unsigned short int  m=0):heure(h),minute(m) {if (h>23||m>59) throw TimeException("erreur: initialisation horaire invalide");}
        void setHoraire(unsigned short int h, unsigned short int m) { if (h>23||m>59) throw TimeException("erreur: initialisation horaire invalide"); heure=h; minute=m; }
        void afficher(QTextStream& f) const;  /*! Affiche l'horaire sous le format hhHmm */
        unsigned short int getHeure() const { return heure; }  /*! Retourne l'heure de l'horaire */
        unsigned short int getMinute() const { return minute; }  /*! Retourne les minutes de l'horaire */
        Horaire* getFin(const Duree& d)const;
        Horaire* getFin(const Duree& d, bool& sur2Jours)const;
        bool operator<(const Horaire& h) const;  /*! h1<h2 retourne true si h1 est avant h2 dans le temps */
        bool operator==(const Horaire& h) const;  /*! h1<h2 retourne true si h1 est au meme temps que h2 dans le temps
                                                     Duree* entre2(const Horaire& h);*/
        Duree *entre2(const Horaire& h);
        static Horaire &fromString(const QString& str);
    private:
        unsigned short int  heure;
        unsigned short int  minute;
    };
QTextStream& operator<<(QTextStream& f, const Horaire& d);

//******************************************************************************************
    /*! \class Periode
            \brief Classe permettant de manipuler des periodes exprimées en jours/mois/années
            L'utilisation de cette classe nécessite des dates valides au sens commun du terme.
            Déclenchement d'exception dans le cas contraire
    */
    class Periode{

        unsigned int nb_jours;
        unsigned int nb_mois;
        unsigned int nb_annees;
    public :
        //! Constructeur à partir de jour/mois/année
        /*! \param j nombre de jours avec 0<=j<=364
            \param m nombre de mois avec 0<=m<=11
            \param a nombre d'années
            */
        Periode(unsigned int j, unsigned int m, unsigned int a);
        void afficher(QTextStream& f) const { f<<"{"<<nb_jours<<" jours, "<<nb_mois<<" mois, "<<nb_annees<<" ans}"; }
    };

//******************************************************************************************
    /*! \class Intervalle
            \brief Classe permettant de manipuler des intervalles de dates
            L'utilisation de cette classe nécessite des dates valides au sens commun du terme.
            Déclenchement d'exception dans le cas contraire
    */
    class Intervalle{
        Date debut;
        Date fin;
    public:
        //! Constructeur à partir de deux dates
        /*! \param d date de début de l'intervalle
            \param f date de fin de l'intervalle. On doit avoir d<=f
            */
        Intervalle(const Date & d, const Date & f);
        void afficher(QTextStream &f) const;  /*! Affiche l'intervalle de dates */
        Date getDebut() const { return debut; }  /*! Retourne la date de début de l'intervalle */
        Date getFin() const { return fin; }  /*! Retourne la date de fin de l'intervalle */
        int getDuree() const { return fin-debut; }  /*! Retourne le nombre de jours s'écoulant entre le début et la fin de l'intervalle */
        bool operator&&(const Intervalle & v) const; /*! I1&&I2 Retourne vrai si il y a intersection entre I1 et I2 */
        Intervalle operator+(const Intervalle & i) const;  /*! I1+I2 Retourne un intervalle union des 2 intervalles I1 et I2 qui se touchent,
                                                ie I2.debut est le jour du lendemain de I1.fin*/
    };

    QTextStream& operator<<(QTextStream& f, const Intervalle& x);

}

#endif // TIMING_H

