#include <QtGui/QApplication>
#include <iostream>
#include "mainwindow.h"
#include "gameControlWidget.h"

using namespace std;

extern int testMap();

extern void testLoadTextures();

Textures Floors::tex("..\\textures\\floor_def.bmp");

int main(int argc, char *argv[])
{
    //testMap();

    cout<<"start"<<endl;
   // testLoadTextures();
    QApplication a(argc, argv);


    GameControlWidget w;
    w.show();

    return a.exec();
}
