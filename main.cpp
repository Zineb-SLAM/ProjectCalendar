#include <QApplication>
#include "agendawindow.h"
#include "splitter.h"

using namespace std;

/*int main()
{
    //TacheU* tache1 = new TacheU("tache numéro 1", Duree(50), Date(4,5,2015), Date(6,5,2015), true, false);
    TacheManager& tacheM = TacheManager::getInstance();
    tacheM.ajouterTacheU("t1", "tache numéro 1", Duree(50), Date(4,5,2015), Date(6,5,2015), true, false);
    QTextStream stdoutQt(stdout);
    tacheM.ajouterTacheU("t2", "tache 2", Duree(25), Date(6,6,1966), Date(6,6,2066));
    tacheM.afficherTaches(stdoutQt);
    //*******************************************Projet**********************************************************************
    ProjetManager& projetM = ProjetManager::getInstance();
    try {
    //projetM.getProjet("p2");
    projetM.creerProjet("p1","premier projet",Date(28,2,1999),Date(20,10,2000));
    projetM.afficherTitreProjets(stdoutQt);
    bool existe = projetM.ProjetExists("p34");
    if(!existe)
        stdoutQt << "le projet n'existe pas" << endl;
    }
    catch(CalendarException e) { stdoutQt << "erreur" << e.getInfo(); }
    catch(TimeException t) { stdoutQt << "erreur TIME" << t.GetInfo(); }
    projetM.removeProject("p1");
    projetM.afficherTitreProjets(stdoutQt);

    //*******************************************Programmation**********************************************************************
    ProgrammationManager& pM = ProgrammationManager::getInstance();
    TacheU* temp=tacheM.getTacheU("t1");
    TacheU* temp2=tacheM.getTacheU("t2");
    pM.ajouterProgrammation(temp, Date(7,6,2015), Horaire(3,20));
    pM.ajouterProgrammation(temp2, Date(10,6,2015), Horaire(18,30));

    //*******************************************Liberer**********************************************************************
    projetM.libererInstance();
    tacheM.libererInstance();
    pM.libererInstance();

    return 0;
}*/


int main(int argc, char* argv[]) {
    QApplication app(argc,argv);
    AgendaWindow fenetre;
    fenetre.show();
    return app.exec();
}

/*int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    splitter w;
    w.show();
    return app.exec();
}*/
