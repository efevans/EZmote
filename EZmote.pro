#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T00:04:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EZmote
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    keylineedit.cpp \
    Clipboard.cpp \
    stringmanager.cpp

HEADERS  += mainwindow.h \
    keylineedit.h \
    Clipboard.h \
    stringmanager.h

FORMS    += mainwindow.ui
