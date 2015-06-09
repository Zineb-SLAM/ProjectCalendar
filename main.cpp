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

int main()
{
    //TacheU* tache1 = new TacheU("tache numéro 1", Duree(50), Date(4,5,2015), Date(6,5,2015), true, false);
    TacheManager& tacheM = TacheManager::getInstance();
    tacheM.ajouterTacheU("tache numéro 1", Duree(50), Date(4,5,2015), Date(6,5,2015), true, false);
    return 0;
}
