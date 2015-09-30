#include "form.h"
#include "ui_form.h"
#include<QMdiArea>
#include<QTextEdit>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    QMdiArea *zoneCentrale = new QMdiArea;
    zoneCentrale->setViewMode(QMdiArea::TabbedView);

        QTextEdit *zoneTexte1 = new QTextEdit;
        QTextEdit *zoneTexte2 = new QTextEdit;

        QMdiSubWindow *sousFenetre1 = zoneCentrale->addSubWindow(zoneTexte1);
        QMdiSubWindow *sousFenetre2 = zoneCentrale->addSubWindow(zoneTexte2);


}

Form::~Form()
{
    delete ui;
}
