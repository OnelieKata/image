#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T15:45:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Image
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fonctions.cpp \
    histo.cpp \
    filtre.cpp

HEADERS  += mainwindow.h \
    fonctions.h \
    histo.h \
    filtre.h

FORMS    += mainwindow.ui
