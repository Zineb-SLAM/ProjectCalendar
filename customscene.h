#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QtWidgets>

class CustomQGraphicsScene : public QGraphicsScene {
    /*! \class CustomQGraphicsScene
            \brief Classe permettant de créer une scene personnalisée
    */
public:
    CustomQGraphicsScene(QObject *parent=0):QGraphicsScene(parent){}
protected:
    void drawBackground(QPainter* painter, const QRectF& rect); //!<dessine un fond personnalisé
};

#endif // CUSTOMSCENE_H

