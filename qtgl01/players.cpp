#include "players.h"
#include "movingobjects.h"

#include <QGLWidget>

Players::Players():
    hp(0),mp(0),sp(0),exp(0),level(0),HALF_WID(4),HALF_HEI(4)
{

    floorY = HALF_HEI;


}

void Players::rendering(){

    glBegin(GL_QUADS);
        glColor3d(0,1,0);
        glVertex3d(x+HALF_WID,y+HALF_HEI,z);
        glVertex3d(x-HALF_WID,y+HALF_HEI,z);
        glVertex3d(x-HALF_WID,y-HALF_HEI,z);
        glVertex3d(x+HALF_WID,y-HALF_HEI,z);
    glEnd();


}

void Players::renderPlayerInfos(const Players&)
{


}

void Players::update(const long MS)
{
    MovingObjects::update(MS);

}

void Players::resetState()
{
    setX(0);
    setY(0);
    setZ(0);
    setVX(0);
    setVY(0);
    setVZ(0);

    setState(this->getNormalState());
}

void Players::handleCollision(  Objects *obj)
{
    //x
    if(obj->getX()> x){
    // right
    // x ---> O
        x=obj->getX()- obj->getWidth()/2-HALF_WID;
        if(x<0)
           x=0;
    }else{
    // left
    // o <--- x

        x=obj->getX()+obj->getWidth()/2+HALF_WID;

    }
    //y
    if(obj->getY()> y){
    //lower
    //  o
    //  |
    //  x

        x=obj->getY()- obj->getHeight()/2+HALF_HEI;

    }else{
     //higher
     //  x
     //  |
     //  o
        x=obj->getY() + obj->getHeight()/2+HALF_HEI;

    }

}

