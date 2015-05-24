#ifndef TACHEEDITEUR_H
#define TACHEEDITEUR_H

#include <QString>
#include <QDate>
#include <QSpinBox>
#include<QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include "Calendar.h"
#include<QTextEdit>
#include <QTextEdit>

class TacheEditeur : public QWidget
{
    Q_OBJECT
    Tache& t;
    QVBoxLayout* vertical;

    // premiere couche Bouton Option
    QHBoxLayout* couche1;
    QLabel*id;
    QLabel * idLineEdit;
    QCheckBox* preemtive;

     // deuxieme couche: Time table
    QHBoxLayout* couche2;
    QLabel*titre;
    QTextEdit * titreTextEdit;



public:
    explicit TacheEditeur(Tache& t, QWidget* parent=0);
signals:

public slots:
   void sauverTache();

};

#endif // TACHEEDITEUR_H

