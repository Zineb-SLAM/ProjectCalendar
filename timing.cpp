#include "timing.h"
void Duree::afficher(QTextStream& f) const
{
    f.setPadChar('0');
    f.setFieldWidth(2);
    f<<nb_minutes/60;
    f.setFieldWidth(0);
    f<<"H";
    f.setFieldWidth(2);
    f<<nb_minutes%60;
    f.setFieldWidth(0);
    f.setPadChar(' ');
}