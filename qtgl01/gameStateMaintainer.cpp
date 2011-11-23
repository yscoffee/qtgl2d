#include "gameStateMaintainer.h"
#include "movingobjects.h"
#include "players.h"
#include "drawutilities.h"
//#include "debugtools.h"

#include <vector>
#include <iostream>
#include <QtEvents>
#include <QtOpenGL>

GameStateMaintainer::GameStateMaintainer(const unsigned int WIDTH, const unsigned int HEIGHT)
    :play1( *(new Players()) ), gameWidgetHeight(HEIGHT),
     gameWidgetWidth(WIDTH),
     currStage( getGSTitle() )
{
    //Players* p1 = new Players();
    tileMap.parseMap("..\\map\\testmap.txt");

    play1.setX(30);
    play1.setY(100);
    play1.setState(play1.getFallState());
    //play1.setfloorY(tileMap.getTileSize()+play1.getHalfHeight() );
    addMovingObj(&play1);

}

void GameStateMaintainer::renderLiveObjs(){

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

void GameStateMaintainer::addMovingObj( MovingObjects * newObj ){
    movingObjsList.push_back(newObj);
}

void GameStateMaintainer::keyboardPressEvent(const QKeyEvent *event)
{
    const int K = event->key();

    if( K == Qt::Key_Up || K == Qt::Key_Space){
        play1.jump();
    }else if( K == Qt::Key_Down ){
       //play1.setVY(play1.getY()-1);

    }else if( K == Qt::Key_Left ){
         play1.setVX( play1.getVX()- Players::MAX_VX );

    }else if( K == Qt::Key_Right ){
        play1.setVX( play1.getVX()+ Players::MAX_VX );

    }else if( K == Qt::Key_P ){
        if( currStage == getGSGaming()|| currStage == getGSPasted())
            currStage=isPasted()?getGSGaming():getGSPasted();

#ifdef __MY_DEBUGS

        std::cout<<"  PAUSED  "<<std::endl;

#endif
    }


}

void GameStateMaintainer::updateObjs(const long MS)
{
/*
#ifdef __MY_DEBUGS
    std::cout<<" px:"<<play1.getX()<<" py:"<<play1.getY()<<std::endl;
#endif
*/
    for(unsigned int ix=0; ix< movingObjsList.size() ;ix++){
        movingObjsList[ix]->update(MS);
    }

    //update panel.

    //collision check.
    Objects * collideTile = tileMap.tileCollisionCheck(play1.getX(),play1.getY(),play1.getHalfWidth()*2,play1.getHalfHeight()*2);

    if(collideTile!=NULL){
        play1.handleCollision(collideTile);

    }else if(play1.getState() == Players::getHighFloorState() ){
        if( tileMap.checkFalling(play1) )
            play1.performFalling(MS);
    }

    if(play1.getX()<0)
        play1.setX(0);
    else if(play1.getX()>tileMap.getMapWidth())
        play1.setX(tileMap.getMapWidth()- play1.getHalfWidth());

    if(play1.getY()<0)
        play1.setY(0);

}

void GameStateMaintainer::rendering()
{
    tileMap.renderingMap(play1.getX(),play1.getY(),play1.getZ(),gameWidgetWidth,gameWidgetHeight);

    renderLiveObjs();
}

void GameStateMaintainer::keyboardReleaseEvent(const QKeyEvent *event)
{

    const int K = event->key();


    if( K == Qt::Key_Left ){

        play1.setVX(0);

    }else if( K == Qt::Key_Right ){
        play1.setVX(0);

    }

}

void GameStateMaintainer::setGameWidgetHeight(const unsigned int H)
{
    gameWidgetHeight=H;
}

void GameStateMaintainer::setGameWidgetWidth(const unsigned int W)
{
    gameWidgetHeight=W;
}

