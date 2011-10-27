#include "gamestate.h"
#include "movingobjects.h"
#include "players.h"
#include <vector>
#include <iostream>
#include <QtEvents>

GameState::GameState():play1( *(new Players()) )
{
    //Players* p1 = new Players();

    play1.setX(-10);
    play1.setY(-10);

    addLiveObj(&play1);

}

void GameState::renderLiveObjs(){
    for(unsigned int ix=0; ix< liveObjs.size() ;ix++){
        liveObjs[ix]->rendering();
    }
    Players::renderPlayerInfos(play1);

}

void GameState::addLiveObj( MovingObjects * newObj ){
    liveObjs.push_back(newObj);
}

void GameState::updateLocation()
{
    for(unsigned int ix=0; ix< liveObjs.size() ;ix++){
        std::cout<<"live obj "<<ix
               <<"x:"<<liveObjs[ix]->getX()
               <<"y:"<<liveObjs[ix]->getY()
               <<std::endl;
    }
}

void GameState::keyboardMovingAction(const QKeyEvent *event)
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
    }

}

