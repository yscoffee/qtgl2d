#include <QtGui/QApplication>
#include <iostream>
#include "mainwindow.h"
#include "gameControlWidget.h"

using namespace std;

int testMap();

int main(int argc, char *argv[])
{
    //testMap();

    cout<<"start"<<endl;

    QApplication a(argc, argv);


    GameControlWidget w;
    w.show();

    return a.exec();
}
