#-------------------------------------------------
#
# Project created by QtCreator 2014-07-24T16:40:44
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT       += network

TARGET = DiceAuth
CONFIG   += console
CONFIG   -= app_bundle
CONFIG +=c++11

TEMPLATE = app


SOURCES += main.cpp \
    diceapi.cpp

HEADERS += \
    diceapi.h
