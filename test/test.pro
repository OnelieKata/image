#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T12:09:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app
INCLUDEPATH += -I/usr/include/opencv
LIBS += -L/usr/lib/ -lopencv_core -lopencv_highgui

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
