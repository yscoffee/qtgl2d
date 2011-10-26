#include "gameControlWidget.h"
#include "ui_gameControlWidget.h"

#include <QtOpenGL>
#include <iostream>
#include <QThread>

GameControlWidget::GameControlWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer),parent),
    ui(new Ui::GameControlWidget),
    deBugON(true),
    idleTimerID(-1),
    trafX(0),trafY(0),trafZ(0)
{

    ui->setupUi(this);

}

GameControlWidget::~GameControlWidget()
{
    delete ui;
}

void GameControlWidget::initializeGL(){

    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    setAutoBufferSwap(true);
    //start idle func
    //QTimer::singleShot(600, this, SLOT(startIdleFunc()));
}
void GameControlWidget::startIdleFunc(){
    //supoose 60fps , redrawing action can be done in the interval.
    redrawTimerID=startTimer(static_cast<int>(1000/60));
}
void GameControlWidget::resizeGL(int width, int height){

    glViewport(200, 300, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    float d = 30;
    //glFrustum(-x, +x, -1.0, +1.0, 4.0, 1000.0);
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0,1000);
    //gluPerspective(3.14*d/360.0,width/height,5,1000);
}




//Display function
void GameControlWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

void GameControlWidget::draw(){
    // Clear The Screen And The Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset The View
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //rotation with fixed point at origin
    /*glRotatef(rotaTheta[0],1,0,0);
    glRotatef(rotaTheta[1],0,1,0);
    glRotatef(rotaTheta[2],0,0,1);
    */
    //Moving Frame(World Coordinate)


    // Drawing square
    //draw3DSquare();

    //mutiple with laster draw objects(vertices)

    glTranslatef(trafX,trafY,trafZ);
       glColor3f(1,1,0.7);
       drawAxs();
       glColor3f(0.5,0.3,0.7);
    int s=50;
    gluLookAt(s,s,s,0,0,0,-1,0,-1);
   // drawAxs();
    gameUpdateAction::renderingMaps(gameState);
    gameUpdateAction::renderingPlayers(gameState);
    gameUpdateAction::renderingEnemies(gameState);
    draw3DSquare();
    glTranslatef(0,0,4);
    draw3DSquare();
    glFlush();

}

void GameControlWidget::drawAxs(){
    glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(100,0,0);
        glVertex3d(0,0,0);
        glVertex3d(0,100,0);
        glVertex3d(0,0,0);
        glVertex3d(0,0,100);
    glEnd();
}

void GameControlWidget::draw3DSquare(){

    glColor3f(0.5f,0.5f,1.0f);							// Set The Color To Blue One Time Only
    glBegin(GL_QUADS);									// Draw A Quad
        glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Blue
        glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f, 1.0f);			// Bottom Left Of The Quad (Top)
        glVertex3f( 1.0f, 1.0f, 1.0f);			// Bottom Right Of The Quad (Top)
        glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
        glVertex3f( 1.0f,-1.0f, 1.0f);			// Top Right Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f, 1.0f);			// Top Left Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Bottom)
        glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Bottom)
        glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
        glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Front)
        glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Front)
        glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Front)
        glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Front)
        glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
        glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Back)
        glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Back)
        glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Back)
        glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Back)
        glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
        glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Left)
        glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Left)
        glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Left)
        glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Left)
        glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
        glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Right)
        glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Right)
        glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Right)
        glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Right)
    glEnd();						// Done Drawing The Quad
}
void GameControlWidget::mouseDoubleClickEvent(QMouseEvent *event){




}

void GameControlWidget::mousePressEvent(QMouseEvent *event){
    std::cout<<"++X="<<event->x()
            <<"Y="<<event->y()<<std::endl;

    if( event->button() == Qt::RightButton)
        this->close();
}
void GameControlWidget::mouseReleaseEvent(QMouseEvent *event){
    std::cout<<"__X="<<event->x()
            <<"Y="<<event->y()<<std::endl;
}
void GameControlWidget::mouseMoveEvent(QMouseEvent *event){
    std::cout<<"\t\tX="<<event->x()
            <<"Y="<<event->y()<<std::endl;
}
void GameControlWidget::timerEvent(QTimerEvent *event){

    if(event->timerId() == redrawTimerID){

        //update angle of rotation value
        for(unsigned int ix=0; ix< 3 ;ix++){
            rotaTheta[ix]+=2.0;
            if(rotaTheta[ix]>360)
                rotaTheta[ix]-=360;
        }
    }

    updateGL();
}
void GameControlWidget::keyReleaseEvent(QKeyEvent *event){

    const int K = event->key();

    if( K == Qt::Key_Up ){
        trafY +=1;
    }else if( K == Qt::Key_Down ){
        trafY -=1;
    }else if( K == Qt::Key_Left ){
        trafX +=1;
    }else if( K == Qt::Key_Right ){
        trafX -=1;
    }else if( K == Qt::Key_Z ){
        trafZ -=5;
    }else if( K == Qt::Key_A ){
        trafZ +=5;
    }else if( K == Qt::Key_Escape || K == Qt::Key_Q ){
        this->close();
    }

    if( deBugON )
        std::cout<<trafX<<' '<<trafY<<' '<<trafZ<<std::endl;
    glFlush();
    updateGL();
}

