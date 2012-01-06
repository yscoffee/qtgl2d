#include "players.h"
#include "movingobjects.h"
#include <iostream>
#include <QGLWidget>
#include "drawutilities.h"

 Textures Players::rightModeTex;
 Textures Players::leftModeTex;

Players::Players():
    hp(0),mp(0),sp(0),exp(0),level(0),HALF_WID(10),HALF_HEI(10),
    preX(0),preY(0),preZ(0),scores(0)
{

    //floorY = HALF_HEI;

}

void Players::rendering(){

    if(isRightDirection)
        DrawUtilities::drawSquareWithTexture(x,y,z,HALF_WID*2,rightModeTex.getTID());
    else
        DrawUtilities::drawSquareWithTexture(x,y,z,HALF_WID*2,leftModeTex.getTID());

    /*glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glColor3d(1,1,1);
        glVertex3d(x+HALF_WID,y+HALF_HEI,z);
        glVertex3d(x-HALF_WID,y+HALF_HEI,z);
        glVertex3d(x-HALF_WID,y-HALF_HEI,z);
        glVertex3d(x+HALF_WID,y-HALF_HEI,z);
    glEnd();
    */

}

void Players::renderPlayerInfos(const int SX, const int SY,QGLWidget * qtw,Players &p)
{
    glColor3f(1,1,1);
    qtw->setFont(QFont("Georgia",23));
    qtw->renderText(-1*SX+50,-1*SY+500,0,QString("$:")+QString::number(p.scores));
}

void Players::update(const int MS)
{
    if(preX!=x)preX=x;
    if(preY!=y)preY=y;
    if(preZ!=z)preZ=z;
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


    int objRight_X=obj->getX() + obj->getWidth()/2;
    int objLeft_X=obj->getX()- obj->getWidth()/2;

    int objHigh_Y=obj->getY() + obj->getHeight()/2;
    int objLow_Y=obj->getY() - obj->getHeight()/2;

    int dx = preX-x;
    int dy = preY-y;
    //int dz = z=preZ;

    int pRight_X=preX+HALF_WID;
    int pLeft_X=preX-HALF_WID;

    int pHigh_Y=preY+HALF_HEI;
    int pLow_Y=preY-HALF_HEI;

    if( 0==dy && ( state == getBottomFloorState()
                  ||  state == getHighFloorState() )){
        //align X
        setVX(0);
       /* if(dx>0){
        //right collision
            setX(objLeft_X);

        }else if(dx<0){
        //left collision
            setX(objRight_X);
        }else{
            std::cerr<<"error dx=0"<<std::endl;
        }*/
        //overlap X test
        if( x+HALF_WID <= objRight_X ){
            //align X, left collided
            setX(objLeft_X-HALF_WID);
            //set VX =0
            setVX(0);

        }else if(x-HALF_WID >= objLeft_X ){
            //align X, right collided
            setX(objRight_X+HALF_WID);
            //set VX =0
            setVX(0);

        }

    }else if( state == getJumpingState()
                ||state == getFallState() ){

        // Determine R|L or U|D collision
        // Use overlapping area to check

        //overlap Y test
        if( pHigh_Y <= objLow_Y ){
            //align Y, lowwer
            setY(objLow_Y-HALF_HEI);
            //set VX =0
            setVY(0);



        }else if(pLow_Y >= objHigh_Y ){
           //align Y, upper
            setY(objHigh_Y+HALF_HEI);
            //set VX =0
            setVY(0);
            if(y < 2*obj->getHeight() )
                setState(getBottomFloorState());
            else
                setState(getHighFloorState());
        }

        bool yAreaStillOverlap = (y-HALF_HEI < objHigh_Y)&&(y-HALF_HEI > objLow_Y)
                                    || (y+HALF_HEI < objHigh_Y)&&(y+HALF_HEI > objLow_Y) ;
        //overlap X test
        if( yAreaStillOverlap && pLeft_X <= objRight_X ){
            //align X, left collided
            setX(objLeft_X-HALF_WID);
            //set VX =0
            setVX(0);

        }else if(yAreaStillOverlap && pRight_X >= objLeft_X ){
            //align X, right collided
            setX(objRight_X+HALF_WID);
            //set VX =0
            setVX(0);

        }


/*
        if( dy   ){
        // up/down collision

            if( dy >=0 ){
            // up collided
                // align Y
                setY(objLow_Y-HALF_HEI);
                setVY(-1*getVY());

            }else{
            // dy <0
            // falling
                //align Y
                setY(objHigh_Y+HALF_HEI);
                setVY(0);
            }

        }else{
        // R|L collision
            //align X
            if(preX > obj->getX() ){
                setX(objLeft_X-HALF_WID);
            }else if(preX < obj->getX() ){
                setX(objRight_X+HALF_WID);
            }else{
                std::cerr<<"logic error"<<std::endl;
            }
            //reset VY
            setVY(0);
        }
*/

    }else {


    }


    /*
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
     */

}

void Players::performFalling(const long MS)
{
    state=getFallState();
    setVY(getVY() - 0.002 * MS);
    //y += vy * MS;
}

void Players::initTexture()
{
    Players::leftModeTex.initial("..\\textures\\player_left.png");
    Players::rightModeTex.initial("..\\textures\\player_right.png");
}

