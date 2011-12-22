#include "gameControlWidget.h"
#include "ui_gameControlWidget.h"
#include "debugtools.h"
#include "drawutilities.h"
#include <QtOpenGL>
#include <iostream>
#include <QThread>
#include "floors.h"

GameControlWidget::GameControlWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer),parent),
    ui(new Ui::GameControlWidget),
    redrawTimerID(-1),
    trafX(0),trafY(0),trafZ(0),
    gameState(this->width(),this->height(),this)
{

    ui->setupUi(this);
    this->setMouseTracking(true);
    initialGameState();
}

GameControlWidget::~GameControlWidget()
{
    delete ui;
}

void GameControlWidget::initializeGL(){

    std::cout<<"gl version:"<<glGetString(GL_VERSION)<<std::endl;
    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    setAutoBufferSwap(true);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    //start idle func after 600ms
    QTimer::singleShot(600, this, SLOT(startIdleFunc()));
    Floors::initTexture("..\\textures\\floor_def.bmp");

}

void GameControlWidget::startIdleFunc(){
    //supoose 60fps , redrawing action can be done in the interval.
    redrawTimerID=startTimer(static_cast<int>(IDLE_REDRAW_MS));

}

void GameControlWidget::resizeGL(int width, int height){

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    float h = height;
    //glFrustum(-h, h, -h ,h, 2.0, 100.0);
    glOrtho(-1*x*h/2, x*h/2, -1*h/2, h/2, 10,2000);
    //gluPerspective(3.14*d/360.0,width/height,5,1000);
    gameState.setGameWidgetHeight(height);
    gameState.setGameWidgetWidth(width);
}

//Display function
void GameControlWidget::paintGL(){
    draw();
}

void GameControlWidget::draw(){
    // Clear The Screen And The Depth Buffer

    glColor3f(1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset The View
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    //Move central point of world frame to the left bottom of screen
    glTranslatef(-1*width()/2,-1*height()/2,-30);

    //Move screen according to game state.
    glTranslatef(gameState.getScrXOffset(width()),gameState.getScrYOffset(height()),0);


    //**********************
    //main route
    gameState.rendering();

    //**********************
    glFlush();

}

void GameControlWidget::drawAxs(){
    glBegin(GL_LINES);
    glVertex3d(-1000,0,0);
    glVertex3d(1000,0,0);
    glVertex3d(0,-1000,0);
    glVertex3d(0,1000,0);
    glVertex3d(0,0,-1000);
    glVertex3d(0,0,1000);
    glEnd();
}


void GameControlWidget::mouseDoubleClickEvent(QMouseEvent *event){

}

void GameControlWidget::mousePressEvent(QMouseEvent *event){

#ifdef __MY_DEBUGS
    std::cout<<"++X="<<event->x()
            <<"Y="<<event->y()<<std::endl;
#endif

}

void GameControlWidget::mouseReleaseEvent(QMouseEvent *event){

#ifdef __MY_DEBUGS
    std::cout<<"__X="<<event->x()
            <<"Y="<<event->y()<<std::endl;
#endif

    if(event->button() == Qt::LeftButton ){

    }else if( event->button() == Qt::RightButton){
        //reset player's location
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0,0,-30);
        std::cout<<"ori: "<<gameState.getPlayerX()
                <<" "<<gameState.getPlayerY()<<std::endl;
        gameState.resetPlayer();
        updateGL();
    }
}

void GameControlWidget::initialGameState()
{ }

void GameControlWidget::timerEvent(QTimerEvent *event){
    if( false == gameState.isPasted() ){
        if(event->timerId() == redrawTimerID){
            gameState.updateObjs(IDLE_REDRAW_MS);
            updateGL();
        }
    }
}
void GameControlWidget::keyReleaseEvent(QKeyEvent *event){
    const int K = event->key();
    gameState.keyboardReleaseEvent(event);
    if( K == Qt::Key_Escape ){
        this->close();
    }

}
void GameControlWidget::keyPressEvent(QKeyEvent *event){

    const int K = event->key();
    //update state
    gameState.keyboardPressEvent(event);

    glFlush();
    updateGL();
}
