#include "customscene.h"

//static const int GRID_STEP = 30;

void CustomQGraphicsScene::drawBackground(QPainter* painter, const QRectF& rect) {
   int gridIntervalH = 100; // intervalle de dessin des lignes verticales
   int gridIntervalV = 25; // intervalle de dessin des lignes horizontales
   painter->setWorldMatrixEnabled(true);

   qreal left = rect.left();
   qreal top = rect.top();

   QVarLengthArray<QLineF, 6> linesX;
   for (qreal x = left; x < rect.right(); x += gridIntervalH )
        linesX.append(QLineF(x, rect.top(), x, rect.bottom()));

   QVarLengthArray<QLineF, 23> linesY;
   for (qreal y = top; y < rect.bottom(); y += gridIntervalV )
        linesY.append(QLineF(rect.left(), y, rect.right(), y));

   // dessin des lignes
   painter->drawLines(linesX.data(), linesX.size());
   painter->drawLines(linesY.data(), linesY.size());
}
