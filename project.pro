#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T23:54:03
#
#-------------------------------------------------

QT       += core gui
QT      += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calendar.cpp \
    timing.cpp \
    table.cpp \
    tache.cpp \
    programmation.cpp \
    evenement.cpp \
    projet.cpp

HEADERS  += mainwindow.h \
    calendar.h \
    timing.h \
    table.h \
    tache.h \
    programmation.h \
    evenement.h \
    projet.h

FORMS    += mainwindow.ui
