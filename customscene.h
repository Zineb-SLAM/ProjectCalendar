#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QtWidgets>

class CustomQGraphicsScene : public QGraphicsScene {
public:
    CustomQGraphicsScene(QObject *parent=0):QGraphicsScene(parent){}
protected:
    void drawBackground(QPainter* painter, const QRectF& rect);
};

#endif // CUSTOMSCENE_H

