#-------------------------------------------------
#
# Project created by QtCreator 2018-03-13T11:03:36
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Battleship
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboard.cpp \
    gamewindow.cpp

HEADERS  += mainwindow.h \
    gameboard.hpp \
    gamewindow.h

FORMS    += mainwindow.ui \
    gamewindow.ui

RESOURCES += \
    pics.qrc

DISTFILES +=
