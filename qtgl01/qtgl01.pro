#-------------------------------------------------
#
# Project created by QtCreator 2011-10-08T03:54:07
#
#-------------------------------------------------

QT      += core gui
QT      += opengl
TARGET = qtgl01
TEMPLATE = app
CONFIG  +=console

SOURCES += main.cpp \
    gameControlWidget.cpp \
    mainwindow.cpp \
    mythreads.cpp \
    gameState.cpp \
    gameUpdateAction.cpp \
    players.cpp \
    movingobjects.cpp

HEADERS  += \
    gameControlWidget.h \
    mainwindow.h \
    mythreads.h \
    gameUpdateAction.h \
    gameState.h \
    players.h \
    movingobjects.h

FORMS    += \
    gameControlWidget.ui \
    mainwindow.ui









































