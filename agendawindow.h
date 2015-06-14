#ifndef AGENDAWINDOW_H
#define AGENDAWINDOW_H

#include <QMainWindow>
#include <QtWidgets> //header qui contient les définitions de toutes les classes widgets

#include "projet.h"
#include "programmation.h"
#include "customscene.h"

class AgendaWindow : public QMainWindow {

    Q_OBJECT

    /*! \class AgendaWindow
            \brief Classe représentant la fenêtre principale de l'application
    */

    //attributs

    TacheManager& TM; /*! instance de TacheManager */
    ProjetManager& PM; /*! instance de ProjetManager */
    ProgrammationManager& ProgM; /*! instance de ProgrammationManager  */

    QWidget *widget_central; /*! widget central */
    QVBoxLayout *general; /*! layout vertical général de la fenêtre */

    //dock widget
    QDockWidget *projets; /*! dock widget pour afficher les projets */
    QTextEdit *liste_projets; /*! liste des projets existants */
    QDockWidget *taches; /*! dock widget pour afficher les taches à programmer */
    QTextEdit *liste_taches; /*! liste des tâches à programmer */

    //menus
    QMenu *menu_options; /*! menu des options */
    QMenu *menu_tache; /*! menu des taches */
    QMenu *menu_projet; /*! menu des projets */
    QMenu *menu_activite; /*! menu des activités  */
    QMenu *menu_Rechercher; /*! menu de recherche  */
    QMenu *menu_arbre; /*! menu de l'arborescence */

    //actions
    QAction *programmer_tache; /*! action programmer une tache */
    //QAction *charger; /*! action charger */
    QAction *exporter; /*! action exporter en XML */
    QAction *exporterTxt; /*! action exporter en texte brut */
    QAction *creer_projet; /*! action créer un projet */
    QAction *Ajouter_tache_a_projet; /*! action ajouter une tache à un projet */
    QAction *creer_tache; /*! action créer une tache */
    QAction *Ajouter_Precedence; /*! action ajouter une précédence à une tache */
    QAction *Ajouter_tache_a_composite; /*! action ajouter une tache à une tache composite */
    QAction *creer_activite; /*! action créer une activité */
    QAction *Rechercher_Projet; /*! action rechercher un projet */
    QAction *Rechercher_Tache; /*! action rechercher une tache */
    QAction *Rechercher_Programmation; /*! action rechercher une programmation */
    QAction *Afficher_projets; /*! action afficher les projets sous forme d'arborescence */
    QAction *Supprimer_tache; /*! action supprimer une tache */
    QAction* Supprimer_projet; /*! action supprimer un projet */
    QAction* Afficher_taches; /*! action afficher les taches sous forme d'arborescence */

    //couche jours
    QLabel *lundi; /*! label lundi */
    QLabel *mardi; /*! label mardi */
    QLabel *mercredi; /*! label mercredi */
    QLabel *jeudi; /*! label jeudi */
    QLabel *vendredi; /*! label vendredi */
    QLabel *samedi; /*! label samedi */
    QLabel *dimanche; /*! label dimanche */
    QHBoxLayout *jours; /*! layout des jours */

    //couche heures
    QLabel *label_00h; /*! label 00h */
    QLabel *label_01h; /*! label 01h */
    QLabel *label_02h; /*! label 02h */
    QLabel *label_03h; /*! label 03h */
    QLabel *label_04h; /*! label 04h */
    QLabel *label_05h; /*! label 05h */
    QLabel *label_06h; /*! label 06h */
    QLabel *label_07h; /*! label 07h */
    QLabel *label_08h; /*! label 08h */
    QLabel *label_09h; /*! label 09h */
    QLabel *label_10h; /*! label 10h */
    QLabel *label_11h; /*! label 11h */
    QLabel *label_12h; /*! label 12h */
    QLabel *label_13h; /*! label 13h */
    QLabel *label_14h; /*! label 14h */
    QLabel *label_15h; /*! label 15h */
    QLabel *label_16h; /*! label 16h */
    QLabel *label_17h; /*! label 17h */
    QLabel *label_18h; /*! label 18h */
    QLabel *label_19h; /*! label 19h */
    QLabel *label_20h; /*! label 20h */
    QLabel *label_21h; /*! label 21h */
    QLabel *label_22h; /*! label 22h */
    QLabel *label_23h; /*! label 23h */
    QVBoxLayout *heures; /*! layout des heures */

    //couche emploi du temps
    CustomQGraphicsScene *scene; /*! scene personnalisée pour l'emploi du temps */
    QGraphicsView *visu; /*! view pour l'emploi du temps */
    QVBoxLayout *emploi_du_temps; /*! layout pour l'emploi du temps */

    //couche agenda
    QHBoxLayout *agenda; /*! layout pour l'agenda */
    QSpacerItem *spacer; /*! espace entre les heures et la table */
    QSpacerItem *spacer2; /*! espace entre les heures et le dock */

    //couche semaine et années
    QSpacerItem *spacer_semaine; /*! spacer entre les semaines et le dock */
    QLabel *s; /*! label semaine */
    QSpinBox *choix_semaine; /*! choix des semaines */
    QLabel *a; /*! label pour les années */
    QSpinBox *choix_annee; /*! choix des années */
    QHBoxLayout *semaine; /*! layout des semaines et années */

    void createActions(); /*! crée les actions */
    void createMenus(); /*! crée les menus */

public:
    explicit AgendaWindow();
signals:
private slots:
    void changer_semaine(); /*! Rafraichit l'affichage de l'emploi du temps en fonction de la semaine choisie */
    void placer_evenement(Activite* a); /*! Place un événement Activite sur l'emploi du temp s*/
    void placer_evenement(TacheU* t); /*! Place un événement TacheU sur l'emploi du temps */
    //void charger_agenda();
    void sauvegarder_agenda(); /*! Sauvegarde l'emploi du temps en format XML */
    void sauvegarder_txt(); /*! Sauvegarde l'emploi du temps en format texte brut */
    void demander_programmer(); /*! Demande la programmation d'un événement à l'utilisateur et le programme */
    void ajouter_projet(); /*! Crée un nouveau projet */
    void ajouter_tache_a_projet(); /*! Ajoute une tache à un projet existant */
    void ajouter_tache(); /*! Crée une nouvelle tache */
    void ajouter_tache_a_composite(); /*! Ajoute une tache à une tache composite existante */
    void ajouter_precedence(); /*! Ajoute une précédence à une tache existante */
    void ajouter_activite(); /*! Crée une nouvelle activité */
    void recherche_projet(); /*! Recherche un projet */
    void recherche_tache(); /*! Recherche une tache */
    void recherche_programmation(); /*! Recherche une programmation */
    void afficher_projets(); /*! Affiche les projets sous forme d'arborescence */
    void supprimer_tache(); /*! Supprime une tache */
    void supprimer_projet(); /*! Supprime un projet */
    void afficher_taches(); /*! Affiche les taches sous forme d'arborescence */


};

class ItemActivite : public QGraphicsItem {
    /*! \class ItemActivite
            \brief Classe permettant de créer un QGraohicsItem personnalisé pour une activité
    */
    Activite* a; /*! pointeur sur une activité existante */
public:
    ItemActivite(Activite* act, QGraphicsItem* parent = 0):QGraphicsItem(parent), a(act) {}
    //fonctions virtuelles pures de QGraphicsItem à implémenter
    QRectF boundingRect() const; /*! crée le bounding rectangle de l'item */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); /*! dessine l'item */
};

class ItemTache : public QGraphicsItem {
    /*! \class ItemTache
            \brief Classe permettant de créer un QGraohicsItem personnalisé pour une tache
    */
    Tache* t; /*! pointeur sur une tache existante */
public:
    ItemTache(Tache* tache, QGraphicsItem* parent = 0):QGraphicsItem(parent), t(tache) {}
    //fonctions virtuelles pures de QGraphicsItem à implémenter
    QRectF boundingRect() const; /*! crée le bounding rectangle de l'item */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); /*! dessine l'item */
};

#endif // AGENDAWINDOW_H
