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

bool Projet::Taskunavalaible(Tache* t)
{
    for(tabtaches::iterator it = tachesProjet.begin(); it != tachesProjet.end(); ++it)
    {
        if((*it)->getId()==t->getId()) return true;
    }
    return false;
}

void Projet::removetache(Tache*t)
{
    unsigned int i;
    for (i=0 ; i<tachesProjet.size();i++)
    {
        if (tachesProjet[i]->getId() == t->getId()) break;
    }
    tachesProjet.erase(tachesProjet.begin()+i);
}

void Projet::addTache(Tache* t) {
    if(Taskunavalaible(t))
    throw CalendarException ("La tache appartient deja au projet");
    tachesProjet.push_back(t);
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

void ProjetManager::creerProjet(const QString& id, const QString& t, const Date& disp, const Date& ech) // cree le projet et le renvoie a addprojet pour l'ajouter
{
    Projet* newp=new Projet(id,t,disp,ech);
    addProjet(newp);
}

bool ProjetManager::Projetexists(const Projet* const p)
{
    for (TabProjet::iterator it = tabprojets.begin(); it!=tabprojets.end(); ++it)
    if (*it == p) return true;
    return false;
}
void ProjetManager::addProjet(Projet* p)
{
    if(Projetexists(p)) throw CalendarException ("Ce projet existe deja");
    tabprojets.push_back(p);
}

void ProjetManager::ajouterTacheAProjet(Projet& p, Tache* t) {
    //vérifier les échances des taches avant d'ajouter au projet
    p.addTache(t);
}

Projet* ProjetManager::getProjet(const QString& id) {
    for (TabProjet::iterator it = tabprojets.begin(); it!=tabprojets.end(); ++it)
    if ((*it)->getId() == id) return *it;
    return 0;
}

void ProjetManager::removeProject(Projet* p)
{
    unsigned int i;
    for (i=0 ; i<tabprojets.size();i++)
    {
        if (tabprojets[i]->getId() == p->getId()) break;
        
    }
    tabprojets.erase(tabprojets.begin()+i);
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
