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

Tache* Projet::Get_Task(const QString& id)
{
    for(tabtaches::iterator it=tachesProjet.begin();it!=tachesProjet.end();it++)
     {
        if((*it)->getId()==id) return (*it);
    }
    throw CalendarException("Tache Inexistante");
}

void Projet::remove_Task(Tache* todelete)
{

    tabtaches::iterator position = std::find(tachesProjet.begin(), tachesProjet.end(), todelete);
    if (position != tachesProjet.end()) // == vector.end() means the element was not found
        tachesProjet.erase(position);

}



void ProjetManager::remove_Task(QString &id)
{
    for(tabprojets::iterator it=projets.begin();it!=projets.end();it++)
    {
        for(std::vector<Tache*>::iterator it2=(*it)->GetTabProjet().begin(); it2!=(*it)->GetTabProjet().end(); it2++)
        {
            if(id==(*it2)->getId())
            {
                    (*it)->remove_Task(*it2);
                    break;// une tache n'existe qu'un fois dans un Projet
            }

        }
    }

}

void Projet::addTache(Tache* t)
{
    if(isTacheDansProjet(t))
        throw CalendarException ("La tache appartient deja au projet");
    double heures_totales=0;
    for(tabtaches::const_iterator it= tachesProjet.begin();it!=tachesProjet.end(); it++)
        heures_totales+=(*it)->getDuree().getDureeEnHeures();

    double duree_projet=(echeance-disponibilite)*24;
    if(duree_projet>heures_totales) tachesProjet.push_back(t);

    else
        throw CalendarException("Vous avez Depassé la Durée Total du Projet");


}


const Tache* Projet::getTache(const QString& id) const
{

    tabtaches::const_iterator it = tachesProjet.begin();
    while (it != tachesProjet.end() && (*it)->getId() != id)
    {

    if (it != tachesProjet.end())
        return *it;
     it++;
    }

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
        if ((*it)->getId() == id)
            return true;
    }
    return false;
}

Projet* ProjetManager::getProjet(const QString& id) {
    for (tabprojets::iterator it = projets.begin(); it!=projets.end(); ++it) {
        if ((*it)->getId() == id)
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

void ProjetManager::ajouterTacheAProjet(Projet* p, Tache* t)
{
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
    try {
    TacheManager& TM = TacheManager::getInstance();
    this->~ProjetManager();
    QString file=f;
    QFile fin(file);
    qDebug()<<"coucou";
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier projets");
    }
    qDebug()<<"coucou";
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        qDebug()<<"coucou";
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        qDebug()<<"coucou";
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        qDebug()<<"coucou";
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            qDebug()<<"coucou";
            // If it's named projets, we'll go to the next.
            if(xml.name() == "projets") continue;
            // If it's named projet, we'll dig the information from there.
            if(xml.name() == "projet") {
                qDebug()<<"new projet\n";
                QString identificateur;
                QString titre;
                Date disponibilite;
                Date echeance;
                
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named projet.
                
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "projet")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificateur.
                        if(xml.name() == "identificateur") {
                            xml.readNext();
                            identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }
                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext();
                            titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found disponibilite.
                        if(xml.name() == "disponibilite") {
                            xml.readNext();
                            disponibilite=Date::fromString(xml.text().toString());
                            qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                        }
                        // We've found echeance.
                        if(xml.name() == "echeance") {
                            xml.readNext();
                            echeance=Date::fromString(xml.text().toString());
                            qDebug()<<"echeance="<<echeance.toString()<<"\n";
                        }
                        // We've found tache.
                        if(xml.name() == "taches") continue;
                            if(xml.name() == "tache") {
                                qDebug()<<"new tache\n";
                                QString id;
                                QString title;
                                Duree time;
                                Date disponibility;
                                Date deadline;

                                xml.readNext();
                                //We're going to loop over the things because the order might change.
                                //We'll continue the loop until we hit an EndElement named projet.

                                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")) {
                                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                        // We've found id.
                                        if(xml.name() == "id") {
                                            xml.readNext();
                                            id=xml.text().toString();
                                            //qDebug()<<"id="<<id<<"\n";
                                        }
                                        // We've found titre.
                                        if(xml.name() == "titre") {
                                            xml.readNext();
                                            title=xml.text().toString();
                                            //qDebug()<<"titre="<<titre<<"\n";
                                        }
                                        // We've found duree.
                                        if(xml.name() == "duree") {
                                            xml.readNext();
                                            time=Duree::fromString(xml.text().toString());
                                            //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                                        }
                                        // We've found disponibilite.
                                        if(xml.name() == "disponibilite") {
                                            xml.readNext();
                                            disponibility=Date::fromString(xml.text().toString());
                                            //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                                        }
                                        // We've found echeance.
                                        if(xml.name() == "echeance") {
                                            xml.readNext();
                                            deadline=Date::fromString(xml.text().toString());
                                            //qDebug()<<"echeance="<<echeance.toString()<<"\n";
                                        }
                                    }
                                    // ...and next...
                                    xml.readNext();
                                }
                                TM.ajouterTacheU(id,title,time,disponibility,deadline);
                                qDebug()<<"ajout_tache";
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
            throw CalendarException(xml.errorString());
        }
        // Removes any device() or data from the reader * and resets its internal state to the initial state.
        xml.clear();
        //qDebug()<<"fin load\n";
    }
    } catch (CalendarException ce) { QMessageBox::information(0,"Erreur",ce.getInfo(),QMessageBox::Ok); }
}

void ProjetManager::save(const QString& f) {
    QString file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
    throw CalendarException(QString("erreur sauvegarde projets  : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("projets");
    for(unsigned int i=0; i<projets.size(); i++) {
        stream.writeStartElement("projet");
        stream.writeTextElement("identificateur",projets[i]->getId());
        stream.writeTextElement("titre",projets[i]->getTitre());
        stream.writeTextElement("disponibilite",projets[i]->getDisponibilite().String());
        stream.writeTextElement("echeance",projets[i]->getEcheance().String());
        stream.writeStartElement("taches");
        Projet::tabtaches taches = projets[i]->GetTabProjet();
        for(unsigned int i=0; i<taches.size(); i++) {
            stream.writeStartElement("tache");
            stream.writeTextElement("id",taches[i]->getId());
            stream.writeTextElement("titre", taches[i]->getTitre());
            stream.writeTextElement("duree", taches[i]->getDuree().toString());
            stream.writeTextElement("disponibilite",taches[i]->getDisponibilite().String());
            stream.writeTextElement("echeance",taches[i]->getEcheance().String());
            stream.writeEndElement();
        }
        stream.writeEndElement();
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void ProjetManager::saveTxt(const QString& f) {
    QString file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde projets  : ouverture fichier xml"));
    QTextStream stream(&newfile);
    stream << "Export des projets" << endl << endl;
    for(unsigned int i=0; i<projets.size(); i++) {
        stream << "Projet " << projets[i]->getId() << endl;
        stream << " titre : " << projets[i]->getTitre() << endl;
        stream << " disponibilite : " << projets[i]->getDisponibilite().toString() << endl;
        stream << " echeance : " << projets[i]->getEcheance().toString() << endl;
        stream << " taches" << endl;
        Projet::tabtaches taches = projets[i]->GetTabProjet();
        for(unsigned int i=0; i<taches.size(); i++) {
            stream << "     tache " << taches[i]->getId() << endl;
            stream << "         titre " << taches[i]->getTitre() << endl;
            stream << "         duree " << taches[i]->getDuree().toString() << endl;
            stream << "         disponibilite " << taches[i]->getDisponibilite().toString() << endl;
            stream << "         echeance " << taches[i]->getEcheance().toString() << endl;
        }
        stream << endl;
    }
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
    QString* s = new QString("");
    for(tabprojets::const_iterator it = projets.begin(); it != projets.end(); it++) {
        s->append((*it)->id);
        s->append("   ");
        s->append((*it)->titre);
        s->append("\n");
    }
    return *s;
}

//******************************************************************************************
