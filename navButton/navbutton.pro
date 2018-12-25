#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:12:35
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = navbutton
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += qt warn_off

SOURCES     += main.cpp
SOURCES     += iconhelper.cpp
SOURCES     += frmnavbutton.cpp
SOURCES     += navbutton.cpp

HEADERS     += frmnavbutton.h
HEADERS     += iconhelper.h
HEADERS     += navbutton.h

FORMS       += frmnavbutton.ui

RESOURCES   += navButttonFont.qrc
