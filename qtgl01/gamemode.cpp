#include "gamemode.h"
#include "gameControlWidget.h"
#include<iostream>

GameMode::GameMode(QGLWidget& P):parent(P),
    play1( *(new Players()) )
{


}

void GameMode::ini()
{
    movingObjsList.clear();
    play1.resetState();
    tileMap.clear();
    tileMap.parseMap("..\\map\\testmap.txt");

    play1.setX(70);
    play1.setY(100);
    play1.setState(play1.getFloorState());
    //play1.setState(play1.getFallState());
    //play1.setfloorY(tileMap.getTileSize()+play1.getHalfHeight() );
    addMovingObj(&play1);
}

void GameMode::updateAction(const long &MS)
{
    for(unsigned int ix=0; ix< movingObjsList.size() ;ix++){
        movingObjsList[ix]->update(MS);
    }
    //handle collision
    try{
        tileMap.tileCollisionHandle(play1);
    }catch(int sig){
        //game end
        gameEnd();
    }catch(...){
        std::cerr<<"unexpeted exp."<<std::endl;
    }
    //out of range align
    if(play1.getX()<0)
        play1.setX(0);
    else if(play1.getX()>tileMap.getMapWorldCoordWidth())
        play1.setX(tileMap.getMapWorldCoordWidth()- play1.getHalfWidth());

    if(play1.getY()<0)
        play1.setY(0);
}

void GameMode::drawAction()
{
    //Move screen according to game state.
    glTranslatef(getScrXOffset(parent.width()),getScrYOffset(parent.height()),0);

    tileMap.renderingMap(play1.getX(),play1.getY(),play1.getZ(),parent.width(),parent.height());
    tileMap.renderingStars(play1.getX(),play1.getY(),play1.getZ(),parent.width(),parent.height(),&parent);
    renderLiveObjs();
}

void GameMode::keyPress(const int &K)
{
    if( K == Qt::Key_Up || K == Qt::Key_Space){
        play1.jump();
    }else if( K == Qt::Key_Down ){
        //play1.setVY(play1.getY()-1);

    }else if( K == Qt::Key_Left ){
        play1.setVX( play1.getVX()- Players::MAX_VX );

    }else if( K == Qt::Key_Right ){
        play1.setVX( play1.getVX()+ Players::MAX_VX );

    }else if( K == Qt::Key_P ){


#ifdef __MY_DEBUGS

        std::cout<<"  PAUSED  "<<std::endl;

#endif
    }else if( K == Qt::Key_Tab ){
        static_cast<GameControlWidget&>(parent).switchMode(GameControlWidget::GS_TitleMode);
    }
}

void GameMode::keyRelease(const int &K)
{
    if( K == Qt::Key_Left ){

        play1.setVX(0);

    }else if( K == Qt::Key_Right ){
        play1.setVX(0);

    }
}

void GameMode::renderLiveObjs()
{
    for(unsigned int ix=0; ix< movingObjsList.size() ;ix++){
        movingObjsList[ix]->rendering();
    }

    //information panel always exist
    Players::renderPlayerInfos(getScrXOffset(parent.width()),getScrYOffset(parent.height()),&parent , play1 );


#ifdef __MYDEBUG_ON
    for(unsigned int ix=0; ix< liveObjs.size() ;ix++){
        std::cout<<"live obj "<<ix
                <<"x:"<<movingObjsList[ix]->getX()
                <<"y:"<<movingObjsList[ix]->getY()
                <<std::endl;
    }
#endif
}

void GameMode::gameEnd()
{
    movingObjsList.clear();
    play1.resetState();
    tileMap.clear();
    static_cast<GameControlWidget&>(parent).switchMode(GameControlWidget::GS_ScoreBoard);
}

