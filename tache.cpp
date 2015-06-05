#include <vector>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QTextStream>
#include "calendar.h"
#include "tache.h"

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

void Tache::ajouterPrecedence(const Tache& t) {
    //à compléter
}

void Tache::supprimerPrecedence(const QString& id) {
    //à compléter
}

//******************************************************************************************

void TacheU::setDuree(const Duree& d) {
    if ((preemptive == false) && (d.getDureeEnHeures() > 12))
            throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
    Tache::setDuree(d);
}

void TacheU::setNonPreemptive() {
        if(getDuree().getDureeEnHeures() > 12)
            throw CalendarException("Erreur tache unitaire : une tache non preemptive ne peut pas avoir une durée supérieure à 12h");
        preemptive = false;
}

QString TacheU::toString() const {
        QTextStream f;
        QString str;
        f<<"**Tache Unitaire** \n";
        if(isPreemptive()) f<<"Tache Preemtive \n";
        if(isProgrammee()) f<<"Tache Programmee \n";
        f>>str;
        return str;
}

//******************************************************************************************

QString TacheC::toString() const {
    QTextStream f;
    QString str;
    f<<"**Tache Composite** \n";
    for(vectcomp::const_iterator it= tachescomp.begin(); it!=tachescomp.end();++it) {
        f<<(*it);
    }
    f>>str;
    return str;
}

//******************************************************************************************

TacheManager::Handler TacheManager::handler=TacheManager::Handler();

TacheManager& TacheManager::getInstance(){
    if (handler.instance==0)
        handler.instance=new TacheManager;
    return *(handler.instance);
}

void TacheManager::libererInstance(){
    if (handler.instance!=0)
        delete handler.instance;
    handler.instance=0;
}

TacheU& TacheManager::ajouterTacheU(const QString& t, const Duree& dur, const Date& dispo, const Date& deadline, const bool& preempt, const bool& prog){
    TacheU* newt = new TacheU(t,dur,dispo,deadline,preempt, prog);
    addItem(newt);
    return *newt;
}

TacheC& TacheManager::ajouterTacheC(const QString& t, const Duree& dur, const Date& dispo, const Date& deadl) {
    TacheC* newt = new TacheC(t,dur,dispo,deadl);
    addItem(newt);
    return *newt;
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

Tache& TacheManager::getTache(const QString& id){
    tabtaches::iterator it = taches.begin();
    while(it!=taches.end() && (*it)->getId() != id) {
        it++;
    }
    if(it!=taches.end()) {
        return **it;
    }
    throw CalendarException("Tache inconnue");
}

void TacheManager::ajouterPrecedenceTache(const Tache& tAjout, const Tache& tPrecedente) {
    //à compléter
}


//******************************************************************************************
