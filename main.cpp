#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include "calendar.h"

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

    /*QString chemin =QFileDialog::getOpenFileName();
     TacheManager& m= TacheManager::getInstance();
     m.load(chemin);
    Tache& t= m.getTache(("T1"));
    identificateur.setText(t.getId());
    titre.setText(t.getTitre());*/

    fenetre.show();

return app.exec();
}
