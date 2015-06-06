// mymodel.cpp
#include "table.h"
#include<QString>
#include<QDebug>
#include<QFont>
#include<QBrush>

MyModel::MyModel(QObject *parent)
    :QAbstractTableModel(parent)
{
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
   return 11;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 7;
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString("Lundi");
            case 1:
                return QString("Mardi");
            case 2:
                return QString("Mercredi");
             case 3:
                return QString("Jeudi");
               case 4:
                return QString ("Vendredi");
            case 5:
                return QString("Samedi");
             case 6:
                return QString("Dimanche");
            }
        }

        if (orientation == Qt::Vertical)
        {
            switch (section)
            {
            case 0:
                return QString("8h-9h");
            case 1:
                return QString("9h-10h");
            case 2:
                return QString("10h-11h");
             case 3:
                return QString("11h-12h");
               case 4:
                return QString ("12h-14h");
            case 5:
                return QString("14h-15h");
             case 6:
                return QString("15h-16h");
             case 7:
                return QString("16h-17h");
              case 8:
                return QString ("17h-18h");
               case 9:
                return QString("18h-19h");
            case 10:
                return QString("19h-20h");
            case 11:
                return QString("20h-21h");
            }
        }

    }
    return QVariant();
}

/*QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
       return QString("Row%1, Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() +1);
    }
    return QVariant();
}*/

QVariant MyModel::data(const QModelIndex &index, int role) const
// doit aussi prendre La Tache en parametre --> recuperer La date et la duree de La tache
{
    int row = index.row();
    int col = index.column();
    // generate a log message when this method gets called
    qDebug() << QString("row %1, col%2, role %3")
            .arg(row).arg(col).arg(role);

    switch(role){
    case Qt::DisplayRole: // on peut se le faire a la rache et ecrire toutes les cases possibles si non on fait une fonction
        if (row == 0 && col == 1) return QString("");
        if (row == 1 && col == 1) return QString("");
        if (row == 0 && col == 1) return QString("");
        if (row == 1 && col == 1) return QString("");
        if (row == 0 && col == 1) return QString("It WORKS!!");
        if (row == 1 && col == 1) return QString("");
        if (row == 0 && col == 1) return QString("");
        if (row == 1 && col == 1) return QString("");
        if (row == 0 && col == 1) return QString("");
        if (row == 1 && col == 1) return QString("");
        if (row == 0 && col == 1) return QString("");
        if (row == 1 && col == 1) return QString("");
}

    return QVariant();
}

