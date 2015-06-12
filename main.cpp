#include <QApplication>
#include "agendawindow.h"
#include "splitter.h"

using namespace std;

<<<<<<< HEAD
int main(int argc, char *argv[])
=======
/*int main()
>>>>>>> origin/master
{


   TacheManager& tacheM = TacheManager::getInstance();
    TacheU& t1=tacheM.ajouterTacheU("t1", "tache numéro 1", Duree(50), Date(4,5,2015), Date(6,5,2015), true,false);
    TacheU& t2=tacheM.ajouterTacheU("t2", "tache 2", Duree(15), Date(6,6,2015), Date(6,6,2015),true,false);
    TacheU& t3=tacheM.ajouterTacheU("t3", "tache 3", Duree(3,30), Date(6,6,2015), Date(6,6,2015));
    TacheU& t4=tacheM.ajouterTacheU("t4", "tache 4", Duree(1,30), Date(4,6,2015), Date(5,6,2015));
    TacheU& t5=tacheM.ajouterTacheU("t5", "tache 5", Duree(55), Date(6,6,2015), Date(6,6,2015));
    TacheU& t6=tacheM.ajouterTacheU("t6", "tache 6", Duree(30), Date(7,6,2015), Date(6,6,2015));
    TacheU& t7= tacheM.ajouterTacheU("t7", "tache 7", Duree(1,40), Date(8,6,2015), Date(6,6,2015));
    TacheU& t8=tacheM.ajouterTacheU("t8", "tache 8", Duree(5,00), Date(9,6,2015), Date(6,6,2015));
    QTextStream stdoutQt(stdout);
    tacheM.afficherTaches(stdoutQt);
    Tache* t = tacheM.getTache("t1");
    ProjetManager& projetM = ProjetManager::getInstance();
        try
    {
        //projetM.getProjet("p2");
        projetM.creerProjet("p1","LO21",Date(28,2,2015),Date(1,10,2015));
        projetM.afficherTitreProjets(stdoutQt);
        Projet* p1=projetM.getProjet("p1");
        projetM.creerProjet("p2","NF17",Date(3,4,2015),Date(20,7,2015));
        projetM.afficherTitreProjets(stdoutQt);
        Projet* p2=projetM.getProjet("p2");
        bool existe = projetM.ProjetExists("p34");
        if(!existe) stdoutQt << "le projet n'existe pas" << endl;
        projetM.afficherTitreProjets(stdoutQt);
        projetM.ajouterTacheAProjet(p1, &t6);
        projetM.ajouterTacheAProjet(p1, &t7);
        projetM.ajouterTacheAProjet(p1, &t2);
        projetM.ajouterTacheAProjet(p2, &t5);
        projetM.ajouterTacheAProjet(p2, &t8);
        projetM.ajouterTacheAProjet(p2, &t1);
        projetM.ajouterTacheAProjet(p2, &t3);
    }

      catch(CalendarException e) { stdoutQt << "erreur" << e.getInfo(); }
    catch(TimeException t) { stdoutQt << "erreur TIME" << t.GetInfo(); }
    /*QApplication app(argc, argv);
    splitter w;
    w.show();
    return app.exec();
    //tacheM.ajouterPrecedenceTache(&t1,&t2);
    //tacheM.ajouterPrecedenceTache(&t2,&t3);
    //tacheM.ajouterPrecedenceTache(&t3,&t4);*/


    //*******************************************Projet**********************************************************************
    /*ProjetManager& projetM = ProjetManager::getInstance();
    try {
    //projetM.getProjet("p2");
    projetM.creerProjet("p1","LO21",Date(28,2,2015),Date(1,10,2015));
    projetM.afficherTitreProjets(stdoutQt);
    Projet* p1=projetM.getProjet("p1");
    projetM.creerProjet("p2","NF17",Date(3,4,2015),Date(20,7,2015));
    projetM.afficherTitreProjets(stdoutQt);
    Projet* p2=projetM.getProjet("p2");
    bool existe = projetM.ProjetExists("p34");
    if(!existe) stdoutQt << "le projet n'existe pas" << endl;
    projetM.afficherTitreProjets(stdoutQt);
    projetM.ajouterTacheAProjet(p1, &t6);
    projetM.ajouterTacheAProjet(p1, &t7);
    projetM.ajouterTacheAProjet(p1, &t6);
    projetM.ajouterTacheAProjet(p2, &t5);
    projetM.ajouterTacheAProjet(p2, &t8);


    }
    catch(CalendarException e) { stdoutQt << "erreur" << e.getInfo(); }
    catch(TimeException t) { stdoutQt << "erreur TIME" << t.GetInfo(); }*/


    //*******************************************Programmation**********************************************************************
    ProgrammationManager& pM = ProgrammationManager::getInstance();
    TacheU* temp=tacheM.getTacheU("t1");
    TacheU* temp2=tacheM.getTacheU("t2");
    Rdv* a= new Rdv("a1","titre1",Duree(1,00),"UTC","Mr");
    pM.ajouterProgrammation(a,Date(02,01,2015),Horaire(2,40));
    pM.ajouterProgrammation(temp, Date(7,6,2015), Horaire(3,20));
    pM.ajouterProgrammation(temp2, Date(10,6,2015), Horaire(18,30));


<<<<<<< HEAD
return 0;
}
=======
    return 0;
}*/
>>>>>>> origin/master


int main(int argc, char* argv[]) {
    QApplication app(argc,argv);
    AgendaWindow fenetre;
    fenetre.show();
<<<<<<< HEAD
     return app.exec();
    //*******************************************Liberer**********************************************************************
     projetM.removeProject("p1");
    projetM.libererInstance();
    tacheM.libererInstance();
    pM.libererInstance();


}*/
=======
    return app.exec();
}
>>>>>>> origin/master

/*int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    splitter w;
    w.show();
    return app.exec();
}*/
