#include <QtGui/QApplication>
#include <iostream>
#include "mainwindow.h"
#include "gameControlWidget.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"start"<<endl;

    QApplication a(argc, argv);

    GameControlWidget w;
    w.show();

    return a.exec();
}
