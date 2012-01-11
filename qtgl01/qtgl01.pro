#-------------------------------------------------
#
# Project created by QtCreator 2011-10-08T03:54:07
#
#-------------------------------------------------

QT      += core gui
QT      += opengl

message($$_PRO_FILE_PWD_)
LIBS  += $$quote(-L$$_PRO_FILE_PWD_/../lib) -lSOIL -lglew32 -lgtest -lopengl32 -lglu32
#win32:LIBS += $$quote($$_PRO_FILE_PWD_/../lib/SOIL.lib)
win32:INCLUDEPATH += $$quote($$_PRO_FILE_PWD_/../include)

win32 {
DEFINES += SDL_WIN
}

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
    testtilemap.h \
    testplayer.h \
    testfloor.h \
    teststar.h

FORMS    += \
    gameControlWidget.ui \
    mainwindow.ui

OTHER_FILES +=































































































