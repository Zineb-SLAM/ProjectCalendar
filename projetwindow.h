#ifndef PROJETWINDOW_H
#define PROJETWINDOW_H

#include <QMainWindow>
#include<QWidget>
#include<QTableView>
#include "calendar.h"
#include "timing.h"
#include "tache.h"
#include "projet.h"

namespace Ui {
class projetwindow;
}

class projetwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit projetwindow(QWidget *parent = 0);
    ~projetwindow();

private:
    Ui::projetwindow *ui;
};


class ItemProjet : public QTableView {
    Projet* p;
public:
    ItemProjet(Projet* Projet, QTableView* parent = NULL):QTableView(parent),p(Projet) {}
    //fonctions virtuelles pures de QGraphicsItem à implémenter


};
#endif // PROJETWINDOW_H
