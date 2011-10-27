#include "gameControlWidget.h"
#include "ui_gameControlWidget.h"

#include <QtOpenGL>
#include <iostream>
#include <QThread>

GameControlWidget::GameControlWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer),parent),
    ui(new Ui::GameControlWidget),
    deBugON(true),
    redrawTimerID(-1),
    trafX(0),trafY(0),trafZ(0),
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

    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);


    setAutoBufferSwap(true);
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0,0,-30);
    //start idle func
   // QTimer::singleShot(600, this, SLOT(startIdleFunc()));

}
void GameControlWidget::startIdleFunc(){
    //supoose 60fps , redrawing action can be done in the interval.
    redrawTimerID=startTimer(static_cast<int>(0));
}
void GameControlWidget::resizeGL(int width, int height){

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    float d = 2;
    glFrustum(-d, d, -d ,d, 2.0, 100.0);
    //glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0,1000);
    //gluPerspective(3.14*d/360.0,width/height,5,1000);
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
    //glLoadIdentity();

    //Moving Frame(World Coordinate)

    //trackball
    if (trackingMouse) {
        glRotatef(angle, axis[0], axis[1], axis[2]);
        glColor3f(0.5,0.3,1);
        drawAxs();
    }
    //testing inf
    glColor3f(1,1,1);
    drawAxs();
    glTranslatef(trafX,trafY,trafZ);
    draw3DSquare();
    //gluLookAt(0,0,s,0,0,0,0,0,-1);
    //---

    //**********************

    gameState.renderLiveObjs();

    //***********************
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

void GameControlWidget::mouseDoubleClickEvent(QMouseEvent *event){


}

void GameControlWidget::mousePressEvent(QMouseEvent *event){
    std::cout<<"++X="<<event->x()
            <<"Y="<<event->y()<<std::endl;

    if(event->button() == Qt::LeftButton ){
        startMotion(event->x(),this->height()-event->y());
    }
}
void GameControlWidget::mouseReleaseEvent(QMouseEvent *event){
    std::cout<<"__X="<<event->x()
            <<"Y="<<event->y()<<std::endl;

    if(event->button() == Qt::LeftButton ){
        stopMotion(event->x(),this->height()-event->y());

    }else if( event->button() == Qt::RightButton){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        angle =0;
        glTranslatef(0,0,-30);

        updateGL();
    }
}


void GameControlWidget::mouseMoveEvent(QMouseEvent *event){
    /*std::cout<<"\t\tX="<<event->x()
            <<"Y="<<event->y()<<"  angle="<<angle
           <<"  ax:"<<axis[0]<<' '<<axis[1]<<' '<<axis[2]
            <<std::endl;
    */
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

void GameControlWidget::timerEvent(QTimerEvent *event){

    if(event->timerId() == redrawTimerID){


    }

    updateGL();
}
void GameControlWidget::keyReleaseEvent(QKeyEvent *event){

    const int K = event->key();

    gameState.keyboardMovingAction(event);

 /*   if( K == Qt::Key_Up ){
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
    }else */ if( K == Qt::Key_Escape || K == Qt::Key_Q ){
        this->close();
    }

    if( deBugON )
        std::cout<<trafX<<' '<<trafY<<' '<<trafZ<<std::endl;
    glFlush();
    updateGL();
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
    a = 1.0F / (float) sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

    v[0] *= a;
    v[1] *= a;
    v[2] *= a;

    return;

}

void GameControlWidget::initialGameState()
{

}
