#include "Calendar.h"
#include "timing.h"
#include <vector>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QTextStream>

using namespace TIME;

//******************************************************************************************
void Tache::setDisponibilite(const Date& d) {
    if (echeance < d)
        throw CalendarException("Erreur Tache : date echeance < nouvelle date disponibilite");
    disponibilite = d;
}

void Tache::setEcheance(const Date& e) {
    if (e < disponibilite)
        throw CalendarException("erreur Tache : nouvelle date echeance < date disponibilite");
    echeance = e;
}

/* on a choisi pour l'instant de le faire avec un QUid
 ---- ne pas supprimer (au cas où on en aurait besoin plus tard ----
 void Tache::setId(const QString& str){
  if (TacheManager::getInstance().isTacheExistante((str))) throw CalendarException("erreur TacheManager : tache id déjà existante");
  identificateur=str;
}
*/

QTextStream& operator<<(QTextStream& fout, const Tache& t){
    fout<<t.getId()<<"\n";
    fout<<t.getTitre()<<"\n";
    fout<<t.getDuree()<<"\n";
    t.getDisponibilite().afficher(fout);
    fout<<"\n";
    t.getEcheance().afficher(fout);
    fout<<"\n";
    return fout;
}

//******************************************************************************************
void TacheU::setDuree(const Duree& d) {
    if ((preemptive == false) && (d.getDureeEnHeures() > 12))
            throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
    Tache::setDuree(d);
}

/*void TacheU::setProgrammee() {
    qDebug()<<"Saisissez La Date et Le temps de La programmation \n";
    unsigned int y,m,d,h,i;
    qDebug()<<"Saisissez l annee \n" ; std::cin>>y;
    qDebug()<<"Saisissez le mois \n"; std::cin>>m;
    qDebug()<<"Saisissez le jour \n"; std::cin>>d;
    Date j(d,m,y);
    qDebug()<<"Saisissez l'heure de l'horaire' \n"; std::cin>>h;
    qDebug()<<"Saisissez les minutes  de l'horaire\n"; std::cin>>i;
    QTime t(h,i);
    programmee = true;
}*/


/*bool TacheC::Precedence(const Tache& t)
{
    for(unsigned int i=0; i<tachescomp.size();i++)
    {
        if (*(tachescomp[i]).getEcheance() > t.getDisponibilite())  return true;
    }
    return false;

}*/

/*void TacheC::ajoutTache(const Tache& t)
{
    if(Precedence(t)) throw CalendarException("Il faut finir les taches précedentes");
    tachescomp.push_back(t);
}*/

//******************************************************************************************
void VPrincipale::addItem(Tache* t) {
        taches.push_back(t);
}

/*Tache* VPrincipale::trouverTache(const QString& t) const { //plus la peine comme les id sont uniques--> Les taches ayant les memes titres?
    for(tabtaches::const_iterator it= taches.begin(); it!=taches.end();++it) {
        //if(id==it->getId()) return (it);
    }
    return 0;
}*/

VPrincipale::~VPrincipale(){
    //if (file!="") save(file);
    for(unsigned int i=0;i<taches.size();i++)
      delete taches[i];
    file="";
}

TacheU& VPrincipale::ajouterTacheU(const QString& t, const Duree& dur, const Date& dispo, const Date& deadline, bool preempt, bool prog)
{
    //if (trouverTache(t)) throw CalendarException("erreur, TacheManager, tache deja existante");
    TacheU* newt = new TacheU(t,dur,dispo,deadline,preempt, prog);
    addItem(newt);
    return *newt;
}

/*Tache& VPrincipale::getTache(const QString& id){
    Tache* t=trouverTache(id);
    if (!t) throw CalendarException("erreur, TacheManager, tache inexistante");
    return *t;
}*/

const Tache& VPrincipale::getTache(const QString& id)const
{
    return const_cast<VPrincipale*>(this)->getTache(id);
}

void VPrincipale::load(const QString& f){
    //qDebug()<<"debut load\n";
    this->~VPrincipale();
    file=f;
    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier taches");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "taches") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "tache") {
                qDebug()<<"new tache\n";
                QString identificateur;
                QString titre;
                Date disponibilite;
                Date echeance;
                Duree duree;
                bool preemptive;

                QXmlStreamAttributes attributes = xml.attributes();
                /* Let's check that Task has attribute. */
                if(attributes.hasAttribute("preemptive")) {
                    QString val =attributes.value("preemptive").toString();
                    preemptive=(val == "true" ? true : false);
                }
                //qDebug()<<"preemptive="<<preemptive<<"\n";

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.


                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "identificateur") {
                            xml.readNext();
                            identificateur=xml.text().toString();
                            //qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext();
                            titre=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found disponibilite
                        if(xml.name() == "disponibilite") {
                            xml.readNext();
                            disponibilite=Date::fromString(xml.text().toString());
                            //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                        }
                        // We've found echeance
                        if(xml.name() == "echeance") {
                            xml.readNext();
                            echeance=Date::fromString(xml.text().toString());
                            //qDebug()<<"echeance="<<echeance.toString()<<"\n";
                        }
                        // We've found duree
                        if(xml.name() == "duree") {
                            xml.readNext();
                            duree=xml.text().toString().toUInt();
                            //qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                //qDebug()<<"ajout tache "<<identificateur<<"\n";
                ajouterTacheU(titre,duree,disponibilite,echeance,preemptive);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw CalendarException("Erreur lecteur fichier taches, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";
}

void VPrincipale::save(const QString& f){
    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde taches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("taches");
    for(unsigned int i=0; i<taches.size(); i++){
        stream.writeStartElement("tache");
        //stream.writeAttribute("preemptive", (taches[i]->isPreemptive())?"true":"false");// isPreemtive dans Taches??
        stream.writeTextElement("identificateur",taches[i]->getId());
        stream.writeTextElement("titre",taches[i]->getTitre());
        stream.writeTextElement("disponibilite",taches[i]->getDisponibilite().toString());
        stream.writeTextElement("echeance",taches[i]->getEcheance().toString());
        QString str;
        str.setNum(taches[i]->getDuree().getDureeEnMinutes());
        stream.writeTextElement("duree",str);
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

//******************************************************************************************
TacheManager::Handler TacheManager::handler=TacheManager::Handler();

TacheManager& TacheManager::getInstance(){
    if (handler.instance==0) handler.instance=new TacheManager();
    return *(handler.instance);
}

void TacheManager::libererInstance(){
    if (handler.instance!=0) delete handler.instance;
    handler.instance=0;
}
//******************************************************************************************
Programmation::Programmation(const Programmation& e) {
    Programmation* x = this;
    *x = Programmation(e.event, e.date, e.horaire);
}

//******************************************************************************************
void ProgrammationManager::addItem(Programmation* t) {
    progs.push_back(t);
}

Programmation* ProgrammationManager::trouverProgrammation(const Event& e) const {
    for(unsigned int i=0; i<progs.size(); i++)
        if (&e==&progs[i]->getEvent()) return progs[i];
    return 0;
}

ProgrammationManager::ProgrammationManager(const ProgrammationManager& e) {
    progs.reserve(e.progs.size());
    for(unsigned int i=0; i<e.progs.size(); i++)
        progs[i] = new Programmation(*e.progs[i]);
}

ProgrammationManager& ProgrammationManager::operator=(const ProgrammationManager& e) {
    if (this==&e) return *this;
    this->~ProgrammationManager();
    for(unsigned int i=0; i<e.progs.size(); i++)
        addItem(new Programmation(*e.progs[i]));
    return *this;
}

ProgrammationManager::Handler ProgrammationManager::handler=ProgrammationManager::Handler();

ProgrammationManager::ProgrammationManager() {
    progs.reserve(10);
}

ProgrammationManager::~ProgrammationManager() {
    for(unsigned int i=0; i<progs.size(); i++)
        delete progs[i];
}

ProgrammationManager& ProgrammationManager::getInstance() {
    if (handler.instance==0) handler.instance=new ProgrammationManager();
    return *(handler.instance);
}

void ProgrammationManager::libererInstance() {
    if (handler.instance!=0) delete handler.instance;
    handler.instance=0;
}

void ProgrammationManager::ajouterProgrammation(const Event& e, const Date& d, const Horaire& h) {
    if (trouverProgrammation(e))
        throw CalendarException("erreur, ProgrammationManager, Programmation deja existante");
    Programmation* newt = new Programmation(e,d,h);
    addItem(newt);
}
