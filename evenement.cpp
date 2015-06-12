#include <vector>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QTextStream>
#include "Calendar.h"
#include "evenement.h"

using namespace TIME;

const QString& Activite::toString() const {
    QString str;
    QTextStream f;
    f << getId() << endl;
    f << getTitre() << endl;
    getDuree().afficher(f);
    f << getLieu() << endl;
    f >> str;
    return str;
}
