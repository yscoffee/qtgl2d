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
    gameUpdateAction.cpp \
    players.cpp \
    movingobjects.cpp \
    objects.cpp \
    staticobjects.cpp \
    floors.cpp \
    debugtools.cpp \
    testMap.cpp \
    gameStateMaintainer.h.cpp \
    tilemap.cpp

HEADERS  += \
    gameControlWidget.h \
    mainwindow.h \
    gameUpdateAction.h \
    players.h \
    movingobjects.h \
    objects.h \
    staticobjects.h \
    floors.h \
    debugtools.h \
    gameStateMaintainer.h \
    tilemap.h

FORMS    += \
    gameControlWidget.ui \
    mainwindow.ui

OTHER_FILES += \
    testmap.txt



































































