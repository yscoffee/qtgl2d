#include "floors.h"
#include "drawutilities.h"
#include <iostream>



Textures Floors::tex;

Floors::Floors()
{
}
Floors::~Floors()
{

}

Floors::Floors(const int X,const int Y,const int Z,const unsigned W,const unsigned int H)
    :Objects(X,Y,Z),width(W),height(H)
{
}

bool Floors::encounterFloor(MovingObjects &obj)
{
    //assume currently floor is a plane with y=1;
    return obj.getY()>=1;
}

void Floors::rendering()
{
    DrawUtilities::drawSquareWithTexture(x,y,z,width,tex.getTID());
   /* Floors::tex.bindTexture();
   // glColor3f(0.7f,0.7f,0.8f);
   // DrawUtilities::draw3DSquare(x,y,z,width);

  glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex3d(x+width/2,y+width/2,z);
        glTexCoord2f(0,1);
        glVertex3d(x-width/2,y+width/2,z);
        glTexCoord2f(0,0);
        glVertex3d(x-width/2,y-width/2,z);
        glTexCoord2f(1,0);
        glVertex3d(x+width/2,y-width/2,z);
   glEnd();
   */
}

void Floors::initTexture()
{
    tex.initial( "..\\textures\\floor_def.png");
}
