#include <vector>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QTextStream>
#include "Calendar.h"
#include "projet.h"

using namespace std;
using namespace TIME;

bool Projet::isTacheDansProjet(Tache* t) {
    for(tabtaches::iterator it = tachesProjet.begin(); it != tachesProjet.end(); ++it) {
        if((*it)->getId()==t->getId())
            return true;
    }
    return false;
}

void Projet::removeTache(Tache*t) {
    unsigned int i;
    for (i=0 ; i<tachesProjet.size();i++) {
        if (tachesProjet[i]->getId() == t->getId())
            tachesProjet.erase(tachesProjet.begin()+i);
    }
}

void Projet::addTache(Tache* t) {
    if(isTacheDansProjet(t))
        throw CalendarException ("La tache appartient deja au projet");
    tachesProjet.push_back(t);
}

const Tache& Projet::getTache(const QString& id) const {
    tabtaches::const_iterator it = tachesProjet.begin();
    while (it != tachesProjet.end() && (*it)->getId() != id)
        it++;
    if (it != tachesProjet.end())
        return **it;
    throw CalendarException("La tache n'appartient pas au projet");
}

void Projet::afficher(QTextStream& f) const {
    f << "Projet " << id << endl;
    f << titre <<endl;
    disponibilite.afficher(f);
    f << endl;
    echeance.afficher(f);
    f << endl << "etat : ";
    if(isTermine())
        f << "termine" << endl;
    else
        f << "non termine" << endl;
}

//******************************************************************************************

ProjetManager::Handler ProjetManager::handler=ProjetManager::Handler();

ProjetManager& ProjetManager::getInstance() {
    if (handler.instance==0)
        handler.instance=new ProjetManager();
    return *(handler.instance);
}

void ProjetManager::libererInstance() {
    if (handler.instance!=0)
        delete handler.instance;
    handler.instance=0;
}

bool ProjetManager::ProjetExists(const QString &id) {
    for (tabprojets::iterator it = projets.begin(); it!=projets.end(); ++it) {
        if ((*it)->id == id)
            return true;
    }
    return false;
}

Projet* ProjetManager::getProjet(const QString& id) {
    for (tabprojets::iterator it = projets.begin(); it!=projets.end(); ++it) {
        if ((*it)->id == id)
            return *it;
    }
    throw CalendarException("Le projet n'existe pas");
}

void ProjetManager::creerProjet(const QString& id, const QString& t, const Date& disp, const Date& ech) { // crée le projet et l'ajoute à la liste des projets existants
    Projet* newp = new Projet(id,t,disp,ech);
    if(ProjetExists(id))
        throw CalendarException ("Ce projet existe deja");
    projets.push_back(newp);
}

void ProjetManager::ajouterTacheAProjet(Projet* p, Tache* t) {
    //vérifier les échances des taches avant d'ajouter au projet
    p->addTache(t);
}

void ProjetManager::removeProject(const QString &id) {
    tabprojets::iterator it = projets.begin();
    while (it != projets.end() && (*it)->id != id)
        it++;
    if(it != projets.end())
        projets.erase(it);
    else
        throw CalendarException("Le projet n'existe pas");
}

void ProjetManager::load(const QString& f) {
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
                QString identificateur;
                QString titre;
                Duree duree;
                Date disponibilite;
                Date echeance;
                
                QXmlStreamAttributes attributes = xml.attributes();
                
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.
                
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "projet")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found id.
                        if(xml.name() == "id") {
                            xml.readNext();
                            identificateur=xml.text().toString();
                            //qDebug()<<"id="<<id<<"\n";
                        }
                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext();
                            titre=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found disponibilite.
                        if(xml.name() == "disponibilite") {
                            xml.readNext();
                            disponibilite=Date::fromString(xml.text().toString());
                            //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                        }
                        // We've found echeance.
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
                creerProjet(identificateur,titre,disponibilite,echeance);
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

void ProjetManager::save(const QString& f) {
    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
    throw CalendarException(QString("erreur sauvegarde projets  : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("taches");
    for(unsigned int i=0; i<projets.size(); i++) {
        stream.writeStartElement("tache");
        //stream.writeAttribute("preemptive", (taches[i]->isPreemptive())?"true":"false");// isPreemtive dans Taches??
        stream.writeTextElement("identificateur",projets[i]->getId());
        stream.writeTextElement("titre",projets[i]->getTitre());
        stream.writeTextElement("disponibilite",projets[i]->getDisponibilite().toString());
        stream.writeTextElement("echeance",projets[i]->getEcheance().toString());
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void ProjetManager::afficherTitreProjets(QTextStream& fout) const {
    fout << "projets" << endl;
    fout << "****" << endl;
    for(tabprojets::const_iterator it = projets.begin(); it != projets.end(); it++) {
        fout << (*it)->titre << endl;
    }
    fout << "****" << endl << "fin des projets" << endl;
}

void ProjetManager::afficherProjets(QTextStream& fout) const {
    fout << "projets" << endl;
    fout << "****" << endl;
    for(tabprojets::const_iterator it = projets.begin(); it != projets.end(); it++) {
        (*it)->afficher(fout);
        fout << "*****";
    }
    fout << endl << "fin des projets" << endl;
}

const QString& ProjetManager::afficherTitreProjets() const {
    QString* s = new QString(" ");
    for(tabprojets::const_iterator it = projets.begin(); it != projets.end(); it++)
        s->append((*it)->titre);
    return *s;
}

//******************************************************************************************
