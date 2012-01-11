#include "gameControlWidget.h"
#include "ui_gameControlWidget.h"
#include "debugtools.h"
#include "drawutilities.h"
#include <QtOpenGL>
#include <iostream>
#include <QThread>
#include "floors.h"
#include "stars.h"
#include "players.h"

GameControlWidget::GameControlWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer),parent),
    ui(new Ui::GameControlWidget),
    redrawTimerID(-1),currHandler(NULL),
    tiltMode(*this),gameMode(*this)
{
    switchMode(GS_TitleMode);

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    setAutoBufferSwap(true);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    //damn
    Floors::initTexture();
    Players::initTexture();
    Stars::initTexture();
    //start idle func after 600ms
    QTimer::singleShot(600, this, SLOT(startIdleFunc()));

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

}

//Display function
void GameControlWidget::paintGL(){
    // Clear The Screen And The Depth Buffer

    glColor3f(1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset The View
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Move central point of world frame to the left bottom of screen
    glTranslatef(-1*width()/2,-1*height()/2,-30);



    //**********************
    //main route

    currHandler->drawAction();

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


}

void GameControlWidget::initialGameState()
{ }

void GameControlWidget::timerEvent(QTimerEvent *event){

    if(event->timerId() == redrawTimerID){
        currHandler->updateAction(IDLE_REDRAW_MS);
        updateGL();
    }
}
void GameControlWidget::keyReleaseEvent(QKeyEvent *event){

    const int K = event->key();


    currHandler->keyRelease(K);
    if( K == Qt::Key_Escape ){
        this->close();
    }

}
void GameControlWidget::keyPressEvent(QKeyEvent *event){

    const int K = event->key();
    //update state
     currHandler->keyPress(K);
    updateGL();
}

void GameControlWidget::switchMode(const GameControlWidget::GameStages S)
{
    this->blockSignals(true);

    switch(S){
        case GS_TitleMode:
            tiltMode.ini();
            currHandler=&tiltMode;
            break;
        case GS_GameMode:
            gameMode.ini();
            currHandler=&gameMode;
            break;
        case GS_GameEnd:
            break;
        case GS_ScoreBoard:
            break;
        default:
            std::cerr<<"error"<<std::endl;
            exit(1);
    }

    this->blockSignals(false);

}


