#include "gameControlWidget.h"
#include "ui_gameControlWidget.h"
#include "debugtools.h"
#include "drawutilities.h"
#include <QtOpenGL>
#include <iostream>
#include <QThread>

GameControlWidget::GameControlWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer),parent),
    ui(new Ui::GameControlWidget),
    redrawTimerID(-1),
    trafX(0),trafY(0),trafZ(0),
    gameState(this->width(),this->height()),
    trackingMouse(false)
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

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    setAutoBufferSwap(true);
    //start idle func after 600ms
    QTimer::singleShot(600, this, SLOT(startIdleFunc()));

    //updateTimerID=startTimer(static_cast<int>(10));

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset The View
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    //Move central point of world frame to the left bottom of screen
    glTranslatef(-1*width()/2,-1*height()/2,-30);

    //trackball function
   /* if (trackingMouse) {
        glRotatef(angle, axis[0], axis[1], axis[2]);
        glColor3f(0.5,0.3,1);
        drawAxs();
    }
    */

    glTranslatef(gameState.getScrXOffset(width()),gameState.getScrYOffset(height()),0);


    //**********************

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

void GameControlWidget::draw3DSquare(){

    glColor3f(0.5f,0.5f,1.0f);							// Set The Color To Blue One Time Only
    glBegin(GL_QUADS);									// Draw A Quad
        glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Blue
        glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f, 1.0f);			// Bottom Left Of The Quad (Top)
        glVertex3f( 1.0f, 1.0f, 1.0f);			// Bottom Right Of The Quad (Top)
        glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
        glVertex3f( 1.0f,-1.0f, 1.0f);			// Top Right Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f, 1.0f);			// Top Left Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Bottom)
        glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Bottom)
        glColor3f(0.7f,0.7f,0.7f);			// Set The Color To Red
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

//HL=half-length of the edges of the square.
void GameControlWidget::draw3DSquare(const int X ,const int Y,const int Z, const int HL=1)
{

    // Set The Color To Blue One Time Only
    glColor3f(0.7f,0.2f,0.8f);

    //X,Y,Z is central point of a 3D box.
    // CCW -defualt mode
    /////////////////////////////////////////////////////////////////////////
    //    v6----- v5
    //   /|      /|
    //  v1------v0|
    //  | |     | |
    //  | |v7---|-|v4
    //  |/      |/
    //  v2------v3
    GLfloat vertices[]={
        X+HL,Y+HL,Z+HL,//v0
        X-HL,Y+HL,Z+HL,//v1
        X-HL,Y-HL,Z+HL,//v2
        X+HL,Y-HL,Z+HL,//v3
        X+HL,Y-HL,Z-HL,//v4
        X+HL,Y+HL,Z-HL,//v5
        X-HL,Y+HL,Z-HL,//v6
        X-HL,Y-HL,Z-HL,//v7
    };
    // color array
    GLfloat colors[] = {1,1,1,  1,1,0,  1,0,0,  1,0,1,              // v0-v1-v2-v3
                        1,1,1,  1,0,1,  0,0,1,  0,1,1,              // v0-v3-v4-v5
                        1,1,1,  0,1,1,  0,1,0,  1,1,0,              // v0-v5-v6-v1
                        1,1,0,  0,1,0,  0,0,0,  1,0,0,              // v1-v6-v7-v2
                        0,0,0,  0,0,1,  1,0,1,  1,0,0,              // v7-v4-v3-v2
                        0,0,1,  0,0,0,  0,1,0,  0,1,1};             // v4-v7-v6-v5

    // index array of vertex array for glDrawElements()
    // Notice the indices are listed straight from beginning to end as exactly
    // same order of vertex array without hopping, because of different normals at
    // a shared vertex. For this case, glDrawArrays() and glDrawElements() have no
    // difference.
    GLubyte indices[] ={ 0,1,2,3,
                         0,3,4,5,
                         0,5,6,1,
                         1,6,7,2,
                         7,4,3,2,
                         4,7,6,5 };

       //glEnableClientState(GL_NORMAL_ARRAY); //Note  flag of lighting sys is turn-off.
       glEnableClientState(GL_COLOR_ARRAY);
       glEnableClientState(GL_VERTEX_ARRAY);

       glColorPointer(3, GL_FLOAT, 0, colors);
       glVertexPointer(3, GL_FLOAT, 0, vertices );
       glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE, indices);

       glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
       glDisableClientState(GL_COLOR_ARRAY);
}

void GameControlWidget::mouseDoubleClickEvent(QMouseEvent *event){

}

void GameControlWidget::mousePressEvent(QMouseEvent *event){

#ifdef __MY_DEBUGS
    std::cout<<"++X="<<event->x()
            <<"Y="<<event->y()<<std::endl;
#endif

    if(event->button() == Qt::LeftButton ){
        startMotion(event->x(),this->height()-event->y());
        lastY=this->height()-event->y();
        lastX=event->x();
    }
}

void GameControlWidget::mouseReleaseEvent(QMouseEvent *event){

#ifdef __MY_DEBUGS
    std::cout<<"__X="<<event->x()
            <<"Y="<<event->y()<<std::endl;
#endif

    if(event->button() == Qt::LeftButton ){
        if(lastX!=event->x()||lastY!=event->y())
            stopMotion(event->x(),this->height()-event->y());

    }else if( event->button() == Qt::RightButton){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        angle =0;
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

    gameState.keyboardPressEvent(event);

    glFlush();
    updateGL();
}

/*
 * ------------------------------------------------------
 * Track ball functions
 *
 *
*/
void GameControlWidget::mouseMoveEvent(QMouseEvent *event){
    if(trackingMouse)
    {
       double curPos[3], dx, dy, dz;

       trackball_ptov(event->x(),event->y(), this->width(), this->height(), curPos);

       dx = curPos[0] - lastPos[0];
       dy = curPos[1] - lastPos[1];
       dz = curPos[2] - lastPos[2];

        if (dx || dy || dz) {

            angle = 90.0F * sqrt(dx*dx + dy*dy + dz*dz);

            axis[0] = lastPos[1]*curPos[2] - lastPos[2]*curPos[1];
            axis[1] = lastPos[2]*curPos[0] - lastPos[0]*curPos[2];
            axis[2] = lastPos[0]*curPos[1] - lastPos[1]*curPos[0];

            lastPos[0] = curPos[0];
            lastPos[1] = curPos[1];
            lastPos[2] = curPos[2];
        }

        updateGL();
    }
}
void GameControlWidget::startMotion(const int X, const int Y){
    //START TRACK
    trackingMouse = true;
    //CLOSE REDRAW
    //cube will follow mourse
    //redrawContinue = false;

    trackball_ptov(X, Y, this->width(),this->height(), lastPos);
}
void GameControlWidget::stopMotion(const int X, const int Y){
    trackingMouse = false;
}
void GameControlWidget::trackball_ptov(int x, int y, int width, int height, double v[3])
{
    float d, a;

    /* project x,y onto a hemi-sphere centered within width, height */

    //normalize
    v[0] = (2.0F*x - width) / width;
    v[1] = ( 2.0F*y- height) / height;
    d = (float) sqrt(v[0]*v[0] + v[1]*v[1]);

    v[2] = (float) cos((M_PI/2.0F) * ((d < 1.0F) ? d : 1.0F));

    //angle = 1/sqrt(v)
    if(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]==0)
        a=0;
    else
        a = 1.0F / (float) sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

    v[0] *= a;
    v[1] *= a;
    v[2] *= a;

    return;

}

//-----------------------------------------------------------
