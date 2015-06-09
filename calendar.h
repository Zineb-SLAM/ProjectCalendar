#ifndef CALENDAR_H
#define CALENDAR_H
#include <QString>
#include <QTextStream>
#include <vector>
#include <QUuid>
#include <sstream>
#include "timing.h"

using namespace std;
using namespace TIME;

//******************************************************************************************
/*! \class CalendarException
        \brief Classe permettant de gérer les exceptions de l'application
*/
class CalendarException
{
    QString info;
public:
    CalendarException(const QString& message) : info(message) {}
    const QString& getInfo() const { return info; }
};

#endif // CALENDAR_H

