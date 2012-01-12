#include "gamemode.h"
#include "gameControlWidget.h"
#include<iostream>
#include<fstream>
#include "backgorund.h"

GameMode::GameMode(QGLWidget& P):parent(P),
    play1( *(new Players()) )
{


}

void GameMode::ini()
{
    movingObjsList.clear();
    play1.resetState();
    tileMap.clear();
    tileMap.parseMap("..\\map\\mapall.txt");

    play1.setX(tileMap.getStartX());
    play1.setY(tileMap.getStartY());
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

    glDisable(GL_BLEND);
    DrawUtilities::drawSquareWithTexture(
            -1*getScrXOffset(parent.width())+parent.width()/2,
            -1*getScrYOffset(parent.height())+parent.height()/2,-2
            ,parent.width(),Backgorund::tex.getTID());

    //information panel always exist
    Players::renderPlayerInfos(getScrXOffset(parent.width()),getScrYOffset(parent.height()),&parent , play1 );

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    renderLiveObjs();
    tileMap.renderingMap(play1.getX(),play1.getY(),play1.getZ(),parent.width(),parent.height());

}

void GameMode::keyPress(const int &K)
{
    if( K == Qt::Key_Up || K == Qt::Key_Space){
        play1.jump();
    }else if( K == Qt::Key_Down ){
        //play1.setVY(play1.getY()-1);
        //play1.setHalfWid(play1.getHalfWidth()/2);
    }else if( K == Qt::Key_Left ){
        play1.setVX( play1.getVX()- Players::MAX_VX );

    }else if( K == Qt::Key_Right ){
        play1.setVX( play1.getVX()+ Players::MAX_VX );

    }else if( K == Qt::Key_P ){


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

    }else if( K == Qt::Key_Down ){
        //play1.setVY(play1.getY()-1);
        //play1.setHalfWid(play1.getHalfWidth()*2);
    }
}

void GameMode::renderLiveObjs()
{
    for(unsigned int ix=0; ix< movingObjsList.size() ;ix++){
        movingObjsList[ix]->rendering();
    }

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
    std::fstream fout("./lastresult.tmp",std::fstream::out);
    fout<<play1.scores<<std::endl;
    fout.close();


    std::fstream records("./score.log",std::fstream::app | std::fstream::out);
    records<<play1.scores<<std::endl;
    records.close();


    movingObjsList.clear();
    play1.resetState();
    tileMap.clear();



    static_cast<GameControlWidget&>(parent).switchMode(GameControlWidget::GS_ScoreBoard);
}

