#ifndef AGENDAWINDOW_H
#define AGENDAWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QDateEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGraphicsView>
#include <QMenuBar>
#include <QMenu>

#include "calendar.h"
#include "timing.h"
#include "tache.h"

class AgendaWindow : public QWidget
{
    Q_OBJECT

    QVBoxLayout *vertical;

    //couche jours
    QLabel *lundi;
    QLabel *mardi;
    QLabel *mercredi;
    QLabel *jeudi;
    QLabel *vendredi;
    QLabel *samedi;
    QLabel *dimanche;
    QHBoxLayout *jours;

    //couche heures
    QLabel *h;
    QLabel *label_00h;
    QLabel *label_01h;
    QLabel *label_02h;
    QLabel *label_03h;
    QLabel *label_04h;
    QLabel *label_05h;
    QLabel *label_06h;
    QLabel *label_07h;
    QLabel *label_08h;
    QLabel *label_09h;
    QLabel *label_10h;
    QLabel *label_11h;
    QLabel *label_12h;
    QLabel *label_13h;
    QLabel *label_14h;
    QLabel *label_15h;
    QLabel *label_16h;
    QLabel *label_17h;
    QLabel *label_18h;
    QLabel *label_19h;
    QLabel *label_20h;
    QLabel *label_21h;
    QLabel *label_22h;
    QLabel *label_23h;
    QVBoxLayout *heures;

    //couche emploi du temps
    QGraphicsView *cadre; //truc graphique pour mettre les tâches
    QHBoxLayout *emploi_du_temps;

    //couche agenda
    QLabel *semaine;
    QSpinBox *choix_semaine;
    QVBoxLayout *agenda;

    //autres éléments
    QMenuBar *barre_menu;
    QMenu *options;

public:
    explicit AgendaWindow(QWidget *parent = 0);
signals:
public slots:
   /* void changer_semaine(const unsigned int& s);
    void placer_tache(const Tache& t);
    void deplacer_tache(const Tache& t);*/
};

#endif // AGENDAWINDOW_H
