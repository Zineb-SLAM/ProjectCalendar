#include "projetwindow.h"
#include "ui_projetwindow.h"

projetwindow::projetwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::projetwindow)
{
    ui->setupUi(this);
}

projetwindow::~projetwindow()
{
    delete ui;
}
