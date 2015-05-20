#include "ajouterTache.h"
#include "calendar.h"
#include <QMessageBox>

 TacheEditeur::TacheEditeur(Tache t,QWidget* parent): t(t),QWidget(parent)
{
    this->vertical= new QVBoxLayout(this);

  // couche1
    couche1= new QHBoxLayout;
    id=new QLabel ("Identificateur", this);
    idLineEdit= new QLineEdit (this);
    preemtive= new QCheckBox (this);
    couche1->addWidget(id);
   couche1->addWidget(idLineEdit);
   couche1->addWidget(preemtive);

   // couche2
   couche2= new QHBoxLayout;
   titre= new QLabel(this);
  titreTextEdit= new QTextEdit(this);
  couche2->addWidget(titre);
  couche2->add>idget(titreTextEdit)

    //couche3
   couche3= new QHBoxLayout;
  dispo=new QLabel ("Disponibilité",this);
  echeance= new QLabel ("Echéance", this);
  duree= new QLabel ("Duree", this);
  dateDispo= new QDateEdit (this);
  dateEcheance= new QDateEdit (this);
  dureeH=new QSpinBox (this);
  dureeM=new QSpinBox (this);
  couche3->addWidget(dispo);
  couche3->addWidget(echeance);
  couche3->addWidget(duree);
  couche3->addWidget(dateDispo);
  couche3->addWidget(dateEcheance);
  couche3->addWidget(dureeH);
   couche3->addWidget(dureeM);

        //couche4
 couche4= new QHBoxLayout;
 annuler= new QPushButton ("Annuler", this);
 save=new QPushButton("Sauver", this);
 couche4->addWidget(annuler);
 couche4->addWidget(save);

  vertical->addItem(couche1);
  vertical->addItem(couche2);
 vertical->addItem(couche3);
 vertical->addItem(couche4);

 idLineEdit->setText(t.getId());
 titreTextEdit->setText(t.getTitre());
 dateDispo->setDate(t.getDateDisponibilite());
 dateEcheance->setDate(t.getDateEcheance());
 dureeH->setValue(t.getDuree().getHeure());
 dureeM->setValue(t.getDuree().getMinute());

 QObject::connnect(annuler, SIGNAL(clicked()),this, SLOT(close()));
QObject::connect(save,SIGNAL(clicked()),this,SLOT(sauverTache()));
QObject::connect()
}

 TacheEditeur::sauverTache()
 {
     if(m.isTacheExistante(idLineEdit->text() && m.getTache(idLineEdit->text())!=&t))
        {

         QMessageBox::warning(this,"ATTENTION", "La tache existe deja" );
         return;
     }
    t.setTitre(titreTextEdit->toPlainText());
    t.setDatesDisponibiliteEcheance(dateDispo->date(),dateEcheance->date());
    t.setDuree(Duree(dureeH->value(), dureeM->value()));
    if(preemtive-> isChecked())
        t.setPreemptive();
    else
        t.setNonPreemptive();

    QMessageBox::information(this,"Sauvegarder","La Tache a été sauvegardée");



 }

 void TacheEditeur::activerButton(QString)
 {
     TacheManager& m=TacheManager::getInstance();
     if(m.)

 }
