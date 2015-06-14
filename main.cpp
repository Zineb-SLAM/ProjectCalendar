#include <QApplication>
#include "agendawindow.h"
#include "splitter.h"
#include"show_info.h"

using namespace std;
/** \author MARTIN Marie & SLAM Zineb */

int main(int argc, char* argv[])
{
 TacheManager& tacheM = TacheManager::getInstance();
    TacheU* t1=tacheM.ajouterTacheU("1", "UML", Duree(50), Date(20,03,2015), Date(6,04,2015));
    TacheU* t2=tacheM.ajouterTacheU("2", "C++", Duree(25,00), Date(10,04,2015), Date(20,05,2015),true,false);
    TacheU* t3=tacheM.ajouterTacheU("3", "Qt", Duree(72,00), Date(21,05,2015), Date(13,06,2015),true,false);
    TacheU* t4=tacheM.ajouterTacheU("4", "SQL", Duree(1,30), Date(4,6,2015), Date(5,6,2015));
    TacheU* t5=tacheM.ajouterTacheU("5", "Prolog", Duree(15,00), Date(04,04,2015), Date(15,06,2015),true,false);
    TacheU* t6=tacheM.ajouterTacheU("6", "Rapport IA02", Duree(5,00), Date(10,6,2015), Date(13,6,2015));
    TacheU* t7= tacheM.ajouterTacheU("7", "Soutenance NF17 ", Duree(20), Date(15,06,2015), Date(15,06,2015));
    TacheU* t8=tacheM.ajouterTacheU("8", "Final IA02 ", Duree(2,00), Date(20,06,2015), Date(20,06,2015));
    TacheU* t9=tacheM.ajouterTacheU("9", "Relationnel", Duree(2,00), Date(03,03,2015), Date(13,03,2015));
    TacheU* t10=tacheM.ajouterTacheU("10", "Tests IA02 ", Duree(2,00), Date(12,06,2015), Date(14,06,2015));
    TacheU* t11=tacheM.ajouterTacheU("11", "Revisions LO21", Duree(24,00), Date(15,06,2015), Date(21,06,2015),true,false);
    TacheU* t12=tacheM.ajouterTacheU("12", "Final LO21", Duree(2,00), Date(21,06,2015), Date(21,06,2015));
    TacheU* t13=tacheM.ajouterTacheU("13", "Final NF17", Duree(2,00), Date(19,06,2015), Date(19,06,2015));
    //TacheC* tc1=tacheM.ajouterTacheC("tc1", "Finaux", Duree(8,00), Date(19,06,2015), Date(25,06,2015));
    QTextStream stdoutQt(stdout);
    tacheM.afficherTaches(stdoutQt);
    //Tache* t = tacheM.getTache("t1");
    ProjetManager& projetM = ProjetManager::getInstance();
     try
    {
        //projetM.getProjet("p2");
        projetM.creerProjet("p1","LO21",Date(28,2,2015),Date(15,06,2015));
        projetM.afficherTitreProjets(stdoutQt);
        Projet* p1=projetM.getProjet("p1");
        projetM.creerProjet("p2","NF17",Date(04,05,2015),Date(20,06,2015));
        projetM.afficherTitreProjets(stdoutQt);
        Projet* p2=projetM.getProjet("p2");
        projetM.afficherTitreProjets(stdoutQt);
         projetM.creerProjet("p3","IA02",Date(03,04,2015),Date(28,06,2015));
        Projet* p3=projetM.getProjet("p3");
        bool existe = projetM.ProjetExists("p34");
        if(!existe) stdoutQt << "le projet n'existe pas" << endl;
        projetM.afficherTitreProjets(stdoutQt);
        /****p1***/
        projetM.ajouterTacheAProjet(p1, t1);
        projetM.ajouterTacheAProjet(p1, t2);
        projetM.ajouterTacheAProjet(p1, t3);
        projetM.ajouterTacheAProjet(p1, t11);
        projetM.ajouterTacheAProjet(p1, t12);
        /****p2***/
        projetM.ajouterTacheAProjet(p2, t10);
        projetM.ajouterTacheAProjet(p2, t4);
        projetM.ajouterTacheAProjet(p2, t9);
        projetM.ajouterTacheAProjet(p2, t7);
        /****p3***/
        projetM.ajouterTacheAProjet(p3, t8);
        projetM.ajouterTacheAProjet(p3, t5);
        projetM.ajouterTacheAProjet(p3, t6);
        projetM.ajouterTacheAProjet(p3, t10);

        tacheM.ajouterPrecedenceTache(t2,t1);//UML precede C++
        tacheM.ajouterPrecedenceTache(t3,t1);// UML precede Qt
        tacheM.ajouterPrecedenceTache(t12,t11);//Les Revisions precedent le Final
         tacheM.ajouterPrecedenceTache(t4,t9);// Relationnel precede SQL
        tacheM.ajouterPrecedenceTache(t3,t2);// C++ precede Qt
         tacheM.ajouterPrecedenceTache(t8,t7);// Soutenance precede Final
        tacheM.ajouterPrecedenceTache(t4,t1);// UML precede SQL
        tacheM.ajouterPrecedenceTache(t7,t5);//Prolog precede la Soutenance
        tacheM.ajouterPrecedenceTache(t7,t10);//Tests precede Soutenance

        ProgrammationManager& pM = ProgrammationManager::getInstance();
        Rdv* a= new Rdv("a1","titre1",Duree(03,00),"UTC","Mr");
        pM.ajouterProgrammation(t1,Date(03,04,2015),Horaire(15,30));
        pM.ajouterProgrammation(t8, Date(22,06,2015), Horaire(8,00));
        pM.ajouterProgrammation(t12, Date(21,06,2015), Horaire(14,30));
        pM.ajouterProgrammation(t2, Date(15,04,2015), Horaire(8,15),Duree(10,00));
        pM.ajouterProgrammation(t2, Date(19,06,2015), Horaire(8,00),Duree(10,00));
        //pM.ajouterProgrammation(t3, Date(21,05,2015), Horaire(10,30));


    //tacheM.ajouter_Tache_a_composite(tc1 ,t8);
   // tacheM.ajouter_Tache_a_composite(tc1 ,t12);
    for (std::vector<Projet*>::iterator it = projetM.getTab().begin(); it!=projetM.getTab().end(); ++it)
    {
        stdoutQt<<"Affichage des taches du projet"<<endl;
        for (unsigned int i =0;i< (*it)->GetTabProjet().size(); i++)
    {
        stdoutQt<<"Tache:";
        stdoutQt<<(*it)->getIndice(i)->getTitre();
        stdoutQt<<endl;
    }
    }

    stdoutQt<<"Precedence:";
    for ( std::vector<TacheU*>::iterator it = t2->getPrecedence().begin(); it!=t2->getPrecedence().end();it++)
    {
        stdoutQt<<"Tache:";
        stdoutQt<<(*it)->getTitre();
    }
}
catch(CalendarException e) { stdoutQt << "erreur" << e.getInfo(); }
catch(TimeException t) { stdoutQt << "erreur TIME" << t.GetInfo(); }


   QApplication app(argc,argv);
    AgendaWindow fenetre;
    fenetre.show();
     return app.exec();


return 0;
}

/*int main(int argc, char* argv[]) {
    QApplication app(argc,argv);
    AgendaWindow fenetre;
    fenetre.show();
     return app.exec();
}*/
//*******************************************Liberer**********************************************************************
/* projetM.removeProject("p1");
projetM.libererInstance();
tacheM.libererInstance();
pM.libererInstance();*/



