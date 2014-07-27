#-------------------------------------------------
#
# Project created by QtCreator 2014-07-24T16:40:44
#
#-------------------------------------------------

QT       += core gui

QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DiceAuth
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp \
    diceapi.cpp \
    mainwindow.cpp \
    filtermodel.cpp

HEADERS += \
    diceapi.h \
    mainwindow.h \
    filtermodel.h

FORMS += \
    mainwindow.ui
