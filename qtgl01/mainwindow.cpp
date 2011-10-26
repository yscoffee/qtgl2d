#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameControlWidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::save(){

}

void MainWindow::load(){

}

void MainWindow::viewRank(){

}

void MainWindow::exit(){
    this->close();
}
