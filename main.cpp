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

/*
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget fenetre;
    fenetre.setFixedSize(220, 220);
    fenetre.move(10,10);

    QLineEdit identificateur(&fenetre);
    QTextEdit titre(&fenetre);
    QPushButton Buton("Save",&fenetre);

    QVBoxLayout couche;
    couche.addWidget(&identificateur);
    couche.addWidget(&titre);
    couche.addWidget(&Buton);
    fenetre.setLayout(&couche);

    QTableView tableView;
    MyModel myModel(0);
    tableView.setModel( &myModel );
    tableView.show();

    fenetre.show();
    return app.exec();
}*/
