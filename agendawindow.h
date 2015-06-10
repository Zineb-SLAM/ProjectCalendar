#ifndef AGENDAWINDOW_H
#define AGENDAWINDOW_H

#include <QtWidgets> //header qui contient les définitions de toutes les classes widgets

#include "calendar.h"
#include "timing.h"
#include "tache.h"

class AgendaWindow : public QMainWindow
{
    Q_OBJECT

    QWidget *widget_central;
    QVBoxLayout *agenda;

    //dock widget
    QDockWidget *projets;
    QTextEdit *liste_projets;

    //menus
    QMenu *menu_options;
    QMenu *menu_tache;
    QAction *programmer_tache;
    QAction *charger;
    QAction *exporter;

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

    //couche semaine
    QLabel *s;
    QSpinBox *choix_semaine;
    QHBoxLayout *semaine;

    void createActions();
    void createMenus();

public:
    explicit AgendaWindow();
signals:
public slots:
   /* void changer_semaine(const unsigned int& s);
    void placer_tache(const Tache& t);
    void deplacer_tache(const Tache& t);*/
};

#endif // AGENDAWINDOW_H
