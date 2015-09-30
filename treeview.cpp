#include "treeview.h"

treeView::treeView(QObject *parent): QAbstractItemModel(parent)
{}
void treeView::data() const
{
    ProjetManager& PM=ProjetManager::getInstance();
    QStandardItemModel* model = new QStandardItemModel();
    QStandardItem *parentItem= model->invisibleRootItem();
     unsigned int i=0;
    for (std::vector<Projet*>::const_iterator it =PM.getInstance().getTab().begin()  ; it!= PM.getInstance().getTab().end() ;it++ )
   {
     QStandardItem* item=new QStandardItem(QString((*it)->getTitre()).arg(i));
     parentItem->appendRow(item);
     parentItem=item;
      i++;
    }
}
