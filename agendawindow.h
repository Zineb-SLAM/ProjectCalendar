#ifndef AGENDAWINDOW_H
#define AGENDAWINDOW_H
#include<QMainWindow>
#include <QtWidgets> //header qui contient les définitions de toutes les classes widgets
#include "calendar.h"
#include "timing.h"
#include "tache.h"
#include "projet.h"

class AgendaWindow : public QMainWindow
{
    Q_OBJECT

    TacheManager& TM;
    ProjetManager& PM;

    QWidget *widget_central;
    QVBoxLayout *general;

    //dock widget
    QDockWidget *projets;
    QTextEdit *liste_projets;

    //menus
    QMenu *menu_options;
    QMenu *menu_tache;
    QMenu *menu_projet;

    //actions
    QAction *programmer_tache;
    QAction *charger;
    QAction *exporter;
    QAction *creer_projet;
    QAction *creer_tache;
    QAction *tout_afficher;

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
    QGraphicsScene *scene;
    QGraphicsView *visu;
    QVBoxLayout *emploi_du_temps;

    //couche agenda
    QHBoxLayout *agenda;
    QSpacerItem *spacer; //espace entre les heures et la table

    //couche semaine
    QSpacerItem *spacer_semaine;
    QLabel *s;
    QSpinBox *choix_semaine;
    QHBoxLayout *semaine;

    void createActions();
    void createMenus();

public:
    explicit AgendaWindow();
signals:
private slots:
    void changer_semaine(const unsigned int& s);
    void placer_tache(const Tache& t);
    void deplacer_tache(const Tache& t);
    void charger_agenda();
    void sauvegarder_agenda();
    void demander_programmer();
    void ajouter_projet();
    void ajouter_tache();
    void afficher();
public slots:
};

class ItemTache : public QGraphicsItem {
    Tache* t;
public:
    ItemTache(Tache* tache, QGraphicsItem* parent = NULL):QGraphicsItem(parent),t(tache) {
        setFlag(QGraphicsItem::ItemIsFocusable);
    }
    //fonctions virtuelles pures de QGraphicsItem à implémenter
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // AGENDAWINDOW_H
