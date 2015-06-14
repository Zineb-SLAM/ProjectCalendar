#ifndef TREEVIEW_H
#define TREEVIEW_H
#include <QObject>
#include<QAbstractTableModel>
#include<QStandardItemModel>
#include "projet.h"
#include<QObject>
#include "programmation.h"
#include "customscene.h"
class treeView : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit treeView(QObject *parent = 0);
    void data() const;

signals:

public slots:
};

#endif // TREEVIEW_H
