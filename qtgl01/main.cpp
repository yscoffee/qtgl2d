#include <QtGui/QApplication>
#include <iostream>
#include "mainwindow.h"
#include "gameControlWidget.h"
#include "testtilemap.h"
#include <gtest/gtest.h>
#include "Textures.h"
using namespace std;

//extern int testMap();
//extern void testLoadTextures();
Textures Floors::tex("..\\textures\\floor_def.bmp");

int main(int argc, char *argv[])
{
    //testMap();
    //testing::InitGoogleTest(&argc, argv);
    //RUN_ALL_TESTS();

    cout<<"start"<<endl;
   // testLoadTextures();
    QApplication a(argc, argv);


    GameControlWidget w;
    w.show();

    return a.exec();
}
