#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include <QTableView>
#include "tache.h"

using namespace std;

int main()
{
    //TacheU* tache1 = new TacheU("tache numéro 1", Duree(50), Date(4,5,2015), Date(6,5,2015), true, false);
    TacheManager& tacheM = TacheManager::getInstance();
    tacheM.ajouterTacheU("t1", "tache numéro 1", Duree(50), Date(4,5,2015), Date(6,5,2015), true, false);
    QTextStream stdoutQt(stdout);
    tacheM.afficher(stdoutQt);
    tacheM.ajouterTacheU("t2", "tache 2", Duree(25), Date(6,6,1966), Date(6,6,2066));
    tacheM.afficherTaches(stdoutQt);
    return 0;
}
