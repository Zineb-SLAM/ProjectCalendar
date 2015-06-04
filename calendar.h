#ifndef CALENDAR_H
#define CALENDAR_H
#include <QString>
#include <QTextStream>
#include <vector>
#include <QUuid>
#include <sstream>
#include "timing.h"
#include "evenement.h"
#include "programmation.h"
#include "projet.h"
#include "tache.h"
#include "timing.h"

using namespace std;
using namespace TIME;

//******************************************************************************************
class CalendarException
{
    QString info;
public:
    CalendarException(const QString& message) : info(message) {}
    QString getInfo() const { return info; }
};

#endif // CALENDAR_H

