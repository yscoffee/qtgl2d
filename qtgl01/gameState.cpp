#include "gamestate.h"
#include "movingobjects.h"
#include "players.h"
#include "debugtools.h"

#include <vector>
#include <iostream>
#include <QtEvents>

GameState::GameState(const unsigned int WIDTH, const unsigned int HEIGHT)
    :play1( *(new Players()) ), gameWidgetHeight(HEIGHT),
     gameWidgetWidth(WIDTH),
      currStage( getGSTitle() )
{
    //Players* p1 = new Players();

    play1.setX(-10);
    play1.setY(-10);

    addMovingObj(&play1);

}

void GameState::renderLiveObjs(){

    for(unsigned int ix=0; ix< movingObjsList.size() ;ix++){
        movingObjsList[ix]->rendering();
    }

    //information panel always exist
    Players::renderPlayerInfos(play1);


#ifdef __MYDEBUG_ON
    for(unsigned int ix=0; ix< liveObjs.size() ;ix++){
        std::cout<<"live obj "<<ix
                <<"x:"<<movingObjsList[ix]->getX()
                <<"y:"<<movingObjsList[ix]->getY()
                <<std::endl;
    }
#endif

}

void GameState::addMovingObj( MovingObjects * newObj ){
    movingObjsList.push_back(newObj);
}


void GameState::keyboardEvent(const QKeyEvent *event)
{
    const int K = event->key();

    if( K == Qt::Key_Up ){
        play1.setY(play1.getY()+1);

    }else if( K == Qt::Key_Down ){
        play1.setY(play1.getY()-1);

    }else if( K == Qt::Key_Left ){
        play1.setX(play1.getX()-1);

    }else if( K == Qt::Key_Right ){
        play1.setX(play1.getX()+1 );

    }else if( K == Qt::Key_Space){

        play1.setState( Players::getJumpingState() );
        play1.setAccY(-1);

    }else if( K == Qt::Key_P ){
        if( currStage == getGSGaming()|| currStage == getGSPasted())
            currStage=isPasted()?getGSGaming():getGSPasted();

#ifdef __MY_DEBUGS

        std::cout<<"  PAUSED  "<<std::endl;

#endif
    }

}

void GameState::updateObjs(const long MS)
{
    if( floor.encounterFloor(play1) ){
        //play1.setY();
        play1.setVY(0);
        play1.setAccY(0);
        play1.setState( Players::getNormalState() );
    }

    for(unsigned int ix=0; ix< movingObjsList.size() ;ix++){
        movingObjsList[ix]->update(MS);
    }
    //update panel
}

