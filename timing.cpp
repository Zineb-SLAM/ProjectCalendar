#include <iomanip>
#include <ctime>
#include <QTextStream>
#include "timing.h"

using namespace TIME;

//******************************************************************************************
void Date::setDate(unsigned short int j, unsigned short int m, unsigned int a) {
    //<!initialisation de la date, renvoie vrai si la date est valide
    if (a>=0&&a<=3000) annee=a; else throw TimeException("erreur: annee invalide");
    if (m>=1&&m<=12) mois=m; else throw TimeException("erreur: mois invalide");
    switch(m){
    case 1: case 3: case 5: case 7: case 8: case 10: case 12: if (j>=1 && j<=31) jour=j; else throw TimeException("erreur: jour invalide"); break;
    case 4: case 6: case 9: case 11: if (j>=1 && j<=30) jour=j; else throw TimeException("erreur: jour invalide"); break;
    case 2: if (j>=1 && (j<=29 || (j==30 && a%4==0))) jour=j; else throw TimeException("erreur: jour invalide"); break;
    }
}

void Date::setDateAujourdhui() {
   //<! initialisation de la date avec la date d'aujourd'hui
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    jour=timeinfo->tm_mday;
    mois=timeinfo->tm_mon+1;
    annee=timeinfo->tm_year+1900;
}

void Date::afficher(QTextStream& f) const {
    // affiche le date sous le format JJ/MM/AAAA
    f.setPadChar('0');
    f.setFieldWidth(2);
    f<<jour;
    f.setFieldWidth(0);
    f<<"/";
    f.setFieldWidth(2);
    f<<mois;
    f.setFieldWidth(0);
    f<<"/";
    f.setFieldWidth(4);
    f<<annee;
    f.setFieldWidth(0);
    f.setPadChar(' ');
}

bool Date::operator==(const Date& d) const {
    if (annee<d.annee) return false;
    if (annee>d.annee) return false;
    if (mois<d.mois) return false;
    if (mois>d.mois) return false;
    if (jour<d.jour) return false;
    if (jour>d.jour) return false;
    return true;
}

bool Date::operator<(const Date& d) const {
    if (annee<d.annee) return true;
    if (annee>d.annee) return false;
    if (mois<d.mois) return true;
    if (mois>d.mois) return false;
    if (jour<d.jour) return true;
    if (jour>d.jour) return false;
    return false;
}

int Date::operator-(const Date& d) const {
    int n=(annee-d.annee)*365+(annee-d.annee)/4;
    n+=int((mois-d.mois)*30.5);
    n+=jour-d.jour;
    return n;
}

Date Date::demain() const {
    Date d=*this;
    d.jour+=1;
    switch(d.mois){
    case 1: case 3: case 5: case 7: case 8: case 10: case 12: if (d.jour==30) { d.jour=1; d.mois++; } break;
    case 4: case 6: case 9: case 11: if (d.jour==31) { d.jour=1; d.mois++; } break;
    case 2: if (d.jour==29 && d.annee%4>0) { d.jour=1; d.mois++; } if (d.jour==30) { d.jour=1; d.mois++; } break;
    }
    if (d.mois==13){ d.annee++; d.mois=1; }
    return d;
}

Date Date::operator+(unsigned int nb_jours) const {
    Date d=*this;
    while(nb_jours>0) { d=d.demain(); nb_jours--; }
    return d;
}

const QString& Date::String() const
{
     QString str= QString::number(this->getAnnee());
    str+="/";str+= QString::number(this->getMois());
    str+="/";str+= QString::number(this->getJour());
    return str;
}

Date Date::fromString(QString s) {
    Date d;
    //conversion QString YYYY-MM-DD en Date
    return d;
}

 QString Date::toString() {
    QString s;
    //conversion Date en QString YYYY-MM-DD
   return s;
}

const QDate& Date::toQDate() const {
    QDate *d = new QDate(jour, mois, annee);
    return *d;
}


//******************************************************************************************
void Duree::afficher(QTextStream& f) const {
    f.setPadChar('0');
    f.setFieldWidth(2);
    f<<nb_minutes/60;
    f.setFieldWidth(0);
    f<<"H";
    f.setFieldWidth(2);
    f<<nb_minutes%60;
    f.setFieldWidth(0);
    f.setPadChar(' ');
}

QTextStream& operator<<(QTextStream& f, const Duree& d)
{ d.afficher(f);
    return f;
}

QTextStream& operator>>(QTextStream& flot, Duree& duree){
    unsigned int h,m;
    bool ok=true;
    flot>>h;
    if (flot.status()!=QTextStream::Ok) ok=false;

    if(flot.read(1)=="H") {
        flot>>m;
        if (flot.status()!=QTextStream::Ok) ok=false;
    }
    else {
        ok=false;
    }
    if (ok) duree=Duree(h,m);
    return flot;
}


//******************************************************************************************
void Horaire::afficher(QTextStream& f) const {
    //anciennement : f<<std::setfill('0')<<std::setw(2)<<heure<<"H"<<std::setfill('0')<<std::setw(2)<<minute<<std::setfill(' ');
    f.setPadChar('0');
    f.setFieldWidth(2);
    f<<heure;
    f.setFieldWidth(0);
    f<<"H";
    f.setFieldWidth(2);
    f<<minute;
    f.setFieldWidth(0);
    f.setPadChar(' ');
}

bool Horaire::operator<(const Horaire& h) const {
    if (heure<h.heure) return true;
    if (heure>h.heure) return false;
    if (minute<h.minute) return true;
    if (minute>h.minute) return false;
    return true;
}
bool Horaire::operator==(const Horaire& h) const {
    if (heure==h.heure) return true;
    if (minute==h.minute) return true;
    return true;
}

QTextStream& operator<<(QTextStream& f, const Horaire& d)
{
    d.afficher(f);
    return f;
}

//******************************************************************************************
Periode::Periode(unsigned int j, unsigned int m, unsigned int a):
           nb_jours(j), nb_mois(m), nb_annees(a) {
    if (j>364) throw TimeException("erreur: initialisation periode invalide");
    if (m>11) throw TimeException("erreur: initialisation periode invalide");
}


//******************************************************************************************
Intervalle::Intervalle(const Date & d, const Date & f):debut(d),fin(f) {
    if (fin<debut) throw TimeException("Erreur dans la creation d'un intervalle: fin<debut");
}

void Intervalle::afficher(QTextStream& f) const {
    f<<"[";
    getDebut().afficher(f);
    f<<" ; ";
    getFin().afficher(f);
    f<<"]";
}

bool Intervalle::operator&&(const Intervalle & v) const {
    if (debut<v.debut){
        if (fin<v.debut) return false; else return true;
    }
    if (v.fin<fin){
        if (v.fin<debut) return false; else return true;
    }
    return true;
}

Intervalle Intervalle::operator+(const Intervalle & i) const {
    Date d=fin.demain();
    if (d==i.debut){
        return Intervalle(debut,i.fin);
    }else throw TimeException("Ne peut pas faire l'union de 2 intervalles (ils ne se touchent pas...");
}

QTextStream& operator<<(QTextStream& f, const Intervalle& x){ x.afficher(f); return f;}


