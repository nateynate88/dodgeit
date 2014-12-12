#-------------------------------------------------
#
# Project created by QtCreator 2014-11-06T15:55:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projecttest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp \
    highscorewindow.cpp \
    gameoverwidget.cpp \
    mainmenu.cpp

HEADERS  += mainwindow.h \
    board.h \
    highscorewindow.h \
    gameoverwidget.h \
    mainmenu.h

FORMS    += mainwindow.ui

CONFIG += c++11
