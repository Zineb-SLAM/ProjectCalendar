#include "Calendar.h"
#include "timing.h"
#include <vector>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QTextStream>

using namespace TIME;

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



//******************************************************************************************
void TacheU::setDuree(const Duree& d) {
    if ((preemptive == false) && (d.getDureeEnHeures() > 12))
            throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
    Tache::setDuree(d);
}

//>>>>>>> Stashed changes


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
void TacheManager::load(const QString& f)
{
    //qDebug()<<"debut load\n";
    this->~TacheManager();
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
                bool program;

                QXmlStreamAttributes attributes = xml.attributes();
                /* Let's check that Task has attribute. */
                if(attributes.hasAttribute("preemptive")) {
                    QString val =attributes.value("preemptive").toString();
                    preemptive=(val == "true" ? true : false);
                }
                //qDebug()<<"preemptive="<<preemptive<<"\n";

                QXmlStreamAttributes attributes_b = xml.attributes();
                /* Let's check that Task has attribute. */
                if(attributes_b.hasAttribute("programmee")) {
                    QString val =attributes_b.value("programmee").toString();
                    program=(val == "true" ? true : false);
                }
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
                ajouterTacheU(titre,duree,disponibilite,echeance,preemptive,program);

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

void TacheManager::save(const QString& f){
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

ProjetManager::Handler ProjetManager::handler=ProjetManager::Handler();

ProjetManager& ProjetManager::getInstance() {
    if (handler.instance==0) handler.instance=new ProjetManager();
    return *(handler.instance);
}

void ProjetManager::libererInstance() {
    if (handler.instance!=0) delete handler.instance;
    handler.instance=0;
}

void ProjetManager::ajouterProjet(const QString& t,const Date& disp, const Date& ech) // cree le projet et le renvoie a addprojet pour l'ajouter
{
     Projet* newp=new Projet(t,disp,ech);
     addprojet(newp);
}
void ProjetManager::addprojet(Projet* p)
{
    tabprojets.push_back(p);
}
void ProjetManager::load(const QString& f)
{
    //qDebug()<<"debut load\n";
    this->~ProjetManager();
    file=f;
    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier projets");
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
                QString titre;
                Date disponibilite;
                Date echeance;

                QXmlStreamAttributes attributes = xml.attributes();

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.

                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "projet")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

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

                    }
                    // ...and next...
                    xml.readNext();
                }
                //qDebug()<<"ajout tache "<<identificateur<<"\n";
                ajouterProjet(titre,disponibilite,echeance);

            {
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
}

void ProjetManager::save(const QString& f)
{
    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde projets  : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("taches");
    for(unsigned int i=0; i<tabprojets.size(); i++)
    {
        stream.writeStartElement("tache");
        //stream.writeAttribute("preemptive", (taches[i]->isPreemptive())?"true":"false");// isPreemtive dans Taches??
        stream.writeTextElement("identificateur",tabprojets[i]->getId());
        stream.writeTextElement("titre",tabprojets[i]->getTitre());
        stream.writeTextElement("disponibilite",tabprojets[i]->getDisponibilite().toString());
        stream.writeTextElement("echeance",tabprojets[i]->getEcheance().toString());
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}


//******************************************************************************************
//******************************************************************************************

ProgrammationManager::Handler ProgrammationManager::handler=ProgrammationManager::Handler();

ProgrammationManager& ProgrammationManager::getInstance() {
    if (handler.instance==0) handler.instance=new ProgrammationManager();
    return *(handler.instance);
}

void ProgrammationManager::libererInstance() {
    if (handler.instance!=0) delete handler.instance;
    handler.instance=0;
}



Programmation* ProgrammationManager::trouverProgrammation(const Event& e) const {
    for(unsigned int i=0; i<tabprogs.size(); i++)
        if (&e==&tabprogs[i]->getEvent()) return tabprogs[i];
    return 0;
}

ProgrammationManager::~ProgrammationManager() {
    for(unsigned int i=0; i<tabprogs.size(); i++)
        delete tabprogs[i];
}

void ProgrammationManager::ajouterProgrammation (const Event& e, const Date& d, const Horaire& h)
{
    if (trouverProgrammation(e))
        throw CalendarException("erreur, ProgrammationManager, Programmation deja existante");
    Programmation* newt = new Programmation(e,d,h);
    addprog(newt);
}
void ProgrammationManager::addprog(Programmation* p)
{

    tabprogs.push_back(p);
}

/*ProgrammationManager::ProgrammationManager(const ProgrammationManager& e) {
    tabprogs.reserve(e.tabprogs.size());
    for(unsigned int i=0; i<e.tabprogs.size(); i++)
        tabprogs[i] = new Programmation(*e.tabprogs[i]);
}

ProgrammationManager& ProgrammationManager::operator=(const ProgrammationManager& e) {
    if (this==&e) return *this;
    this->~ProgrammationManager();
    for(unsigned int i=0; i<e.tabprogs.size(); i++)
        addprog(new Programmation(*e.tabprogs[i]));
    return *this;
}*/








