#ifndef STARS_H
#define STARS_H
#include <QtOpenGL>
#include "drawutilities.h"
#include <QGLWidget>
#include "objects.h"
#include "textures.h"
class Stars : public Objects
{
private:
    static Textures tex;

public:

    Stars(const int X,const int Y, const int Z);
    virtual void rendering()const{
        DrawUtilities::drawSquareWithTexture(x,y,z,LENGTH,Stars::tex.getTID());
    }

    //Call by Timer. Be used to update state of game object
    //Unit of time is millisecond second
    virtual void update(const int ){}
    virtual int getWidth(){return LENGTH;}
    virtual int getHeight(){return LENGTH;}
    /*void rendering(QGLWidget*qtw)const{
        //glColor3f(0.0f,1.0f,0.8f);
        DrawUtilities::drawSquareWithTexture(x,y,z,LENGTH,Stars::tex.getTID());
        /*glBegin(GL_QUADS);
            glVertex3d(x+LENGTH/2,y+LENGTH/2,z);
            glVertex3d(x-LENGTH/2,y+LENGTH/2,z);
            glVertex3d(x-LENGTH/2,y-LENGTH/2,z);
            glVertex3d(x+LENGTH/2,y-LENGTH/2,z);
        glEnd();* /

    }*/
    static const int LENGTH = 30;
    static void initTexture();
};

#endif // STARTS_H
