#-------------------------------------------------
#
# Project created by QtCreator 2015-11-27T17:56:25
#
#-------------------------------------------------

QT       += core gui
QT       += webkitwidgets
QT       += multimedia
QT       +=sql
QT       +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CloudMusic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    source.qrc
