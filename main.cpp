#include <QApplication>
#include "agendawindow.h"

using namespace std;

/*int main()
{
    //TacheU* tache1 = new TacheU("tache numéro 1", Duree(50), Date(4,5,2015), Date(6,5,2015), true, false);
    TacheManager& tacheM = TacheManager::getInstance();
    tacheM.ajouterTacheU("t1", "tache numéro 1", Duree(50), Date(4,5,2015), Date(6,5,2015), true, false);
    QTextStream stdoutQt(stdout);
    tacheM.ajouterTacheU("t2", "tache 2", Duree(25), Date(6,6,1966), Date(6,6,2066));
    tacheM.afficherTaches(stdoutQt);
    ProjetManager& projetM = ProjetManager::getInstance();
    try {
    //projetM.getProjet("p2");
    projetM.creerProjet("p1","premier projet",Date(28,2,1999),Date(20,10,2000));
    projetM.afficherTitreProjets(stdoutQt);
    bool existe = projetM.ProjetExists("p34");
    if(!existe)
        stdoutQt << "le projet n'existe pas" << endl;
    } catch(CalendarException e) { stdoutQt << "erreur" << e.getInfo(); }
    catch(TimeException t) { stdoutQt << "erreur TIME" << t.GetInfo(); }
    projetM.removeProject("p1");
    projetM.afficherTitreProjets(stdoutQt);
    projetM.libererInstance();
    tacheM.libererInstance();
    return 0;
}*/


int main(int argc, char* argv[]) {
    QApplication app(argc,argv);
    AgendaWindow fenetre;
    fenetre.show();
    return app.exec();
}
