#include "players.h"
#include "movingobjects.h"

#include <QGLWidget>

Players::Players():
    hp(0),mp(0),sp(0),exp(0),level(0),HALF_WID(4),HALF_HEI(4)
{

    //floorY = HALF_HEI;

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
    setX(50);
    setY(50);
    setZ(0);
    setVX(0);
    setVY(0);
    setVZ(0);

    setState(this->getBottomFloorState());
}

void Players::handleCollision( Objects *obj)
{
    //check it's a valid request
    if( obj == NULL )
        return;

    int pRight_X=x+HALF_WID;
    int pLeft_X=x-HALF_WID;

    int pHigh_Y=y+HALF_HEI;
    int pLow_Y=y-HALF_HEI;

    int objRight_X=obj->getX() + obj->getWidth()/2;
    int objLeft_X=obj->getX()- obj->getWidth()/2;

    int objHigh_Y=obj->getY() + obj->getHeight()/2;
    int objLow_Y=obj->getY() - obj->getHeight()/2;

    //first check X-Axis
    // left
    //   [--O--]
    //     [--P--]
    bool xLCol=objRight_X > pLeft_X && pLeft_X >= objLeft_X ;
    // right
    //    [--O--]
    //[--P--]
    bool xRCol= (!xLCol) && ( pRight_X > objLeft_X &&  objRight_X > pRight_X ) ;

    //check Y-Axis
    // p
    // |
    // v
    // obj
    bool yFallCol=pLow_Y > objLow_Y && objHigh_Y > pLow_Y;
    // obj
    // ^
    // |
    // p
    bool yJumpCol=(!yFallCol)&&(state!= getFallState() &&pHigh_Y > objLow_Y && objHigh_Y > pHigh_Y);



     if( (xLCol||xRCol) && (yFallCol||yJumpCol) ){

         if(xLCol){
             setVX(0);

             //if player is falling, not allign x-axis
           if(getVY()==0)
             setX(objRight_X+getHalfWidth());
         }else{
         //X R collision
             setVX(0);
             //if player is falling, not allign x-axis
           if(getVY()==0)
             setX(objLeft_X-getHalfWidth());
         }

         if(yJumpCol){
             if(getVY()>0)
                 setVY(-1*getVY());


         }else{
         //Y bottom
             if( getY() >  obj->getHeight()+getHalfHeight() )
                 setState(Players::getHighFloorState() );
             else
                 setState(Players::getBottomFloorState() );
             setVY(0);
             setY(objHigh_Y+getHalfHeight());

         }

     }

}

void Players::performFalling(const long MS)
{
    state=getFallState();
    setVY(getVY() - 0.002 * MS);
    y += vy * MS;
}

