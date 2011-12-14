#-------------------------------------------------
#
# Project created by QtCreator 2011-10-08T03:54:07
#
#-------------------------------------------------

QT      += core gui
QT      += opengl

message($$_PRO_FILE_PWD_)
LIBS  += $$quote(-L$$_PRO_FILE_PWD_/../lib)
LIBS  +=  -lglew32 -lgtest
win32:INCLUDEPATH += $$quote($$_PRO_FILE_PWD_/../include)
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
    tilemap.cpp \
    drawutilities.cpp \
    gameStateMaintainer.cpp \
    textures.cpp \
    testTextures.cpp \
    stars.cpp

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
    tilemap.h \
    drawutilities.h \
    textures.h \
    stars.h \
    testtilemap.h

FORMS    += \
    gameControlWidget.ui \
    mainwindow.ui

OTHER_FILES +=


























































































