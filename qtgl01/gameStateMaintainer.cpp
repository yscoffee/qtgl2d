#include "gameStateMaintainer.h"
#include "movingobjects.h"
#include "players.h"
#include "drawutilities.h"
//#include "debugtools.h"
#include "floors.h"
#include <vector>
#include <iostream>
#include <QtEvents>
#include <QtOpenGL>



GameStateMaintainer::GameStateMaintainer(const unsigned int WIDTH, const unsigned int HEIGHT,QGLWidget*QP)
    :play1( *(new Players()) ), gameWidgetHeight(HEIGHT),gameWidgetWidth(WIDTH),parent(QP),
      currStage( GS_Title ),titleCoice(0)
{

    tileMap.parseMap("..\\map\\testmap.txt");

    play1.setX(70);
    play1.setY(100);
    play1.setState(play1.getFloorState());
    //play1.setState(play1.getFallState());
    //play1.setfloorY(tileMap.getTileSize()+play1.getHalfHeight() );
    addMovingObj(&play1);


}

void GameStateMaintainer::renderLiveObjs(){

    for(unsigned int ix=0; ix< movingObjsList.size() ;ix++){
        movingObjsList[ix]->rendering();
    }

    //information panel always exist
    Players::renderPlayerInfos(getScrXOffset(parent->width()),getScrYOffset(parent->height()),parent , play1 );


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

    switch(currStage){
        case GS_Title:
            titleKeyPress(K);
            break;
        case GS_Gaming:
            gamingKeyPress(K);
            break;
        case GS_Pasted:
            break;
        case GS_GameEnd:
            gameEndKeyPress(K);
            break;
        case GS_ScoreBoard:
            scoreBoardKeyPress(K);
            break;
        default:
        std::cerr<<"error "<<__LINE__<<std::endl;
    }



}

void GameStateMaintainer::updateObjs(const long MS)
{


    switch(currStage){
        case GS_Title:
            titleUpdate(MS);
            break;
        case GS_Gaming:
            gamingUpdate(MS);
            break;
        case GS_Pasted:
            break;
        case GS_GameEnd:
            gameEndUpdate(MS);
            break;
        case GS_ScoreBoard:
            scoreBoardUpdate(MS);
            break;
        default:
        std::cerr<<"error "<<__LINE__<<std::endl;
    }



}

void GameStateMaintainer::draw()
{

    switch(currStage){
        case GS_Title:
            drawTitle();
            break;
        case GS_Gaming:
            darwGaming();
            break;
        case GS_Pasted:
            break;
        case GS_GameEnd:
            drawGameEnd();
            break;
        case GS_ScoreBoard:
            drawScoreBoard();
            break;
        default:
        std::cerr<<"error "<<__LINE__<<std::endl;
    }


}

void GameStateMaintainer::keyboardReleaseEvent(const QKeyEvent *event)
{

    const int K = event->key();



    switch(currStage){
        case GS_Title:
            titleKeyRelease(K);
            break;
        case GS_Gaming:
            gamingKeyRelease(K);
            break;
        case GS_Pasted:
            break;
        case GS_GameEnd:
            gameEndKeyRelease(K);
            break;
        case GS_ScoreBoard:
            scoreBoardRelease(K);
            break;
        default:
        std::cerr<<"error "<<__LINE__<<std::endl;
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

void GameStateMaintainer::darwGaming()
{
    tileMap.renderingMap(play1.getX(),play1.getY(),play1.getZ(),gameWidgetWidth,gameWidgetHeight);
    tileMap.renderingStars(play1.getX(),play1.getY(),play1.getZ(),gameWidgetWidth,gameWidgetHeight,parent);
    renderLiveObjs();
}

void GameStateMaintainer::titleUpdate(const long &MS)
{
}

void GameStateMaintainer::gamingUpdate(const long &MS)
{

    for(unsigned int ix=0; ix< movingObjsList.size() ;ix++){
        movingObjsList[ix]->update(MS);
    }
    //test hard collision
    tileMap.tileCollisionCheck(play1);

    //test soft collision(star)
    bool stCool = tileMap.starsCollisionCheck(play1.getX(),play1.getY(),play1.getHalfWidth()*2,play1.getHalfHeight()*2);
    if(stCool){
        play1.scores++;
    }

    //out of range align
    if(play1.getX()<0)
        play1.setX(0);
    else if(play1.getX()>tileMap.getMapWidth())
        play1.setX(tileMap.getMapWidth()- play1.getHalfWidth());

    if(play1.getY()<0)
        play1.setY(0);
}

void GameStateMaintainer::gameEndUpdate(const long &MS)
{
}

void GameStateMaintainer::scoreBoardUpdate(const long &MS)
{
}

void GameStateMaintainer::titleKeyPress(const int &K)
{
    if( K == Qt::Key_Down ){

        titleCoice=(++titleCoice)%3;

    }else if( K == Qt::Key_Up ){
        titleCoice=(--titleCoice)%3;
    }else if( K == Qt::Key_Enter || K == Qt::Key_Space ){
        //enter new state
        switch(titleCoice){
            case 1 :
                break;
            case 2 :
                break;
            case 3 :
                break;
            default: break;
        }
    }

}

void GameStateMaintainer::gamingKeyPress(const int &K)
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
        if( currStage == getGSGaming()|| currStage == getGSPasted())
            currStage=isPasted()?getGSGaming():getGSPasted();

#ifdef __MY_DEBUGS

        std::cout<<"  PAUSED  "<<std::endl;

#endif
    }


}

void GameStateMaintainer::scoreBoardKeyPress(const int &)
{
}

void GameStateMaintainer::gameEndKeyPress(const int &)
{
}

void GameStateMaintainer::titleKeyRelease(const int & K)
{

}

void GameStateMaintainer::gamingKeyRelease(const int & K)
{
    if( K == Qt::Key_Left ){

        play1.setVX(0);

    }else if( K == Qt::Key_Right ){
        play1.setVX(0);

    }
}

void GameStateMaintainer::gameEndKeyRelease(const int &)
{
}

void GameStateMaintainer::scoreBoardRelease(const int &)
{
}

void GameStateMaintainer::drawTitle()
{
    glColor3f(1,1,1);
    // window coordinates
    // with the origin in the upper left-hand corner of the window
    parent->setFont(QFont("Georgia",50));
    parent->renderText(parent->width()/3,parent->height()/4,QString("JJJJJump!"));

    //render menu
    static QFont listFont=QFont("Georgia",20);
    static int dx = parent->width()*2/5;
    static int dy = parent->height()/2;
    static QString gs = QString(">  Game Start");
    static QString sb = QString(">  Score Board");
    static QString exit = QString(">  Exit");

    glColor3f(0.5,0.5,0.5);
    parent->renderText(dx,dy,gs,listFont);
    parent->renderText(dx,dy+40,sb,listFont);
    parent->renderText(dx,dy+80,exit,listFont);

    glColor3d(0,0,1);
    //parent->renderText(dx,dy+titleCoice*40,QString(">"),listFont);
    switch(titleCoice){
        case 0:
            parent->renderText(dx,dy,gs,listFont);
            break;
        case 1:
            parent->renderText(dx,dy+40,sb,listFont);
            break;
        case 2:
            parent->renderText(dx,dy+80,exit,listFont);
            break;
        default:
        break;
    }
}

void GameStateMaintainer::drawGameEnd()
{
}

void GameStateMaintainer::drawScoreBoard()
{
}

