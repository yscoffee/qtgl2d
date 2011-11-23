#ifndef STARS_H
#define STARS_H
#include <QtOpenGL>
#include "drawutilities.h"
#include <QGLWidget>
#include "objects.h"

class Stars : public Objects
{
public:
    Stars(const int X,const int Y, const int Z);
    virtual void rendering(){}//do redering in other side. temp design

    //Call by Timer. Be used to update state of game object
    //Unit of time is millisecond second
    virtual void update(const int ){}
    void rendering(QGLWidget*qtw){
        glColor3f(0.0f,1.0f,0.8f);
        //DrawUtilities::draw3DSquare(x,y,z,LENGTH);
        //qtw->setFont(QFont("Times",17));
        //qtw->renderText(getX(),getY(),QString("*"));
    glBegin(GL_QUADS);
        glVertex3d(x+LENGTH/2,y+LENGTH/2,z);
        glVertex3d(x-LENGTH/2,y+LENGTH/2,z);
        glVertex3d(x-LENGTH/2,y-LENGTH/2,z);
        glVertex3d(x+LENGTH/2,y-LENGTH/2,z);
    glEnd();

    }
    static const int LENGTH = 10;
     virtual int getWidth(){return LENGTH;}
     virtual int getHeight(){return LENGTH;}
};

#endif // STARTS_H
