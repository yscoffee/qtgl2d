#include "players.h"
#include "movingobjects.h"
#include <iostream>
#include <QGLWidget>
#include "drawutilities.h"

 Textures Players::rightModeTex;
 Textures Players::leftModeTex;

 Textures Players::fallRModeTex;
 Textures Players::fallLModeTex;
Players::Players():
    hp(0),mp(0),sp(0),exp(0),level(0),halfWidth(20),halfHeight(20),
    preX(0),preY(0),preZ(0),scores(0)
{
}

void Players::rendering()const{

    if( vy == 0){
        if(isRightDirection)
            DrawUtilities::drawSquareWithTexture(x,y,z,halfWidth*2,rightModeTex.getTID());
        else
            DrawUtilities::drawSquareWithTexture(x,y,z,halfWidth*2,leftModeTex.getTID());
    }else{
        if(isRightDirection)
            DrawUtilities::drawSquareWithTexture(x,y,z,halfWidth*2,fallRModeTex.getTID());
        else
            DrawUtilities::drawSquareWithTexture(x,y,z,halfWidth*2,fallLModeTex.getTID());

    }
}

void Players::renderPlayerInfos(const int SX, const int SY,QGLWidget * qtw,Players &p)
{
    glColor3f(1,1,1);
    qtw->setFont(QFont("Papyrus",23));
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
    setX(70);
    setY(70);
    setZ(0);
    setVX(0);
    setVY(0);
    setVZ(0);
    scores=0;
    setState(this->getFloorState());
}
void Players::initTexture()
{
    Players::leftModeTex.initial("..\\textures\\player_move_L.png");
    Players::rightModeTex.initial("..\\textures\\player_move_R.png");
    Players::fallLModeTex.initial("..\\textures\\player_jump_L.png");
    Players::fallRModeTex.initial("..\\textures\\player_jump_R.png");
}

void Players::jump()
{
    if(state==getFloorState()){
        state=getJumpingState();
        MovingObjects::jump();
    }
}

