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

void Floors::rendering()const
{
    DrawUtilities::drawSquareWithTexture(x,y,-1,width,tex.getTID());

}

void Floors::initTexture()
{
    tex.initial( "..\\textures\\floor_def.png");
}
