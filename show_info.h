#ifndef SHOW_INFO_H
#define SHOW_INFO_H
#include "show_info.h"
#include "calendar.h"
#include "timing.h"
#include "tache.h"
#include "projet.h"
#include"programmation.h"
#include <QObject>
#include <QWidget>
#include<QLabel>
#include<QDialog>
#include<QFormLayout>

class ProjetInfoId : public QDialog
{
    Q_OBJECT

    QLabel* id;
    QLabel* titre;
    QLabel* disponibilite;
    QLabel* echeance;
    QLabel* taches;
   QFormLayout* formLayout;

public:
    ProjetInfoId(const QString& id,QWidget* parent=0,Qt::WindowFlags f = 0);

};

class ProjetInfo : public QDialog
{
    Q_OBJECT

    QLabel* id;
    QLabel* titre;
    QLabel* disponibilite;
    QLabel* echeance;
    QLabel* taches;
   QFormLayout* formLayout;

public:
    ProjetInfo(Projet* p,QWidget* parent=0,Qt::WindowFlags f = 0);

};


class TacheInfo : public QDialog {
    Q_OBJECT

    QLabel* id;
    QLabel* titre;
    QLabel* duree;
    QLabel* disponibilite;
    QLabel* echeance;
    QLabel* taches;
    QLabel* type;
    QLabel* preemtive;
    QLabel* precedente;
    QLabel* suivante;

    QFormLayout* formLayout;

public:
    TacheInfo(Tache* t,QWidget* parent=0,Qt::WindowFlags f = 0);

};




#endif // SHOW_INFO_H
