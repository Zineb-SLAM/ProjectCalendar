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

    // premiere couche
    QHBoxLayout* couche1;
    QLabel*id;
    QLabel * idLineEdit;
    QCheckBox* preemtive;

     // deuxieme couche
    QHBoxLayout* couche2;
    QLabel*titre;
    QTextEdit * titreTextEdit;

    // troisieme couche
    QHBoxLayout* couche3;
    QLabel* dispo,*echeance,*duree;
    QDateEdit *dateDispo,*dateEcheance;
    QSpinBox *dureeH,*dureeM;

    // quatrieme couche
    QHBoxLayout* couche4;
    QPushButton *annuler,*save;

public:
    explicit TacheEditeur(Tache& t, QWidget* parent=0);
signals:

public slots:
   void sauverTache();

};
    #endif // TACHEEDITEUR_H

