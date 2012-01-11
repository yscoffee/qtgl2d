#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "players.h"
#include "floors.h"
#include "movingobjects.h"
#include "staticobjects.h"
#include "tilemap.h"
//#include "debugtools.h"
#include <QtEvents>
#include <vector>
#include <cmath>
#include <QGLWidget>
#include <map>
#include <string>


class GameStateMaintainer
{

private:
    enum GameStages{ GS_Title , GS_Gaming, GS_Pasted, GS_ScoreBoard ,GS_GameEnd };
    //interface
     class Runnable{
     public:
         virtual void run()=0;
         virtual const char* getName()=0;
     };

     class Gaming:public Runnable{
         virtual void run(){}
         virtual const char* getName(){
             return "Game Start";
         }
     };

     class Title:public Runnable{
         virtual void run(){}
         virtual const char* getName(){
             return "Game Start";
         }
     };

     class Exit:public Runnable{
         virtual void run(){}
         virtual const char* getName(){
             return "Game Start";
         }
     };

public:
    GameStateMaintainer(const unsigned int WIDTH, const unsigned int HEIGHT,QGLWidget*);

    void renderLiveObjs();
    void renderFloors();
    void draw();

    void updateObjs(const long MS);

    void addMovingObj(MovingObjects *);
    void keyboardPressEvent(const QKeyEvent *);
    void keyboardReleaseEvent(const QKeyEvent *);
    void setGameWidgetHeight(const unsigned int );
    void setGameWidgetWidth(const unsigned int );
    void resetPlayer(){ play1.resetState();}
    inline
    bool isPasted(){return currStage==GS_Pasted;}

    inline
    GameStages getGSGaming(){return GS_Gaming;}
    inline
    GameStages getGSPasted(){return GS_Pasted;}
    inline
    GameStages getGSTitle(){return GS_Title;}
    inline
    int getMapWidth(){return tileMap.getMapWidth();}
    inline
    int getMapHeight(){return tileMap.getMapHeight();}
    inline
    int getPlayerX(){return play1.getX();}
    inline
    int getPlayerY(){return play1.getY();}
    void addFloor(Floors * );

    int getScrXOffset(const int S_WID){
#ifdef __MY_DEBUGS
        static int c=0;c++;
#endif
        if( play1.getX()+S_WID/2 > tileMap.getMapWidth() ){
#ifdef __MY_DEBUGS
                std::cout<<"TX"<<c<<' '<<-1*(tileMap.getMapWidth() - S_WID )<<std::endl;
#endif
            return -1*std::abs(static_cast<float>(tileMap.getMapWidth() - S_WID ));

        }else if( (play1.getX()- S_WID/2.0) <0  ){
#ifdef __MY_DEBUGS
                std::cout<<c<<' '<<"TX retu 0"<<std::endl;
#endif
                return 0;
        }else{
#ifdef __MY_DEBUGS
            std::cout<<"TX else"<<c<<' '<<-1*(play1.getX()-S_WID/2.0)<<std::endl;
#endif
            return -1*std::abs(static_cast<float>(play1.getX()-S_WID/2.0));
        }

    }
    int getScrYOffset(const int S_HEI){
        if( play1.getY()  - S_HEI/2 >0 )
            return -1*(play1.getY() -  S_HEI/2);
         else
           return 0;
    }

private:

    void darwGaming();
    void drawTitle();
    void drawGameEnd();
    void drawScoreBoard();

    void titleUpdate(const long &MS);
    void gamingUpdate(const long &MS);
    void gameEndUpdate(const long &MS);
    void scoreBoardUpdate(const long &MS);

    void titleKeyPress(const int& );
    void gamingKeyPress(const int& );
    void gameEndKeyPress(const int& );
    void scoreBoardKeyPress(const int& );

    void titleKeyRelease(const int &);
    void gamingKeyRelease(const int &);
    void gameEndKeyRelease(const int &);
    void scoreBoardRelease(const int &);


    QGLWidget * parent;
    int playerTrans_Y;

    Players& play1;
    Floors floor;

    std::vector<MovingObjects *> movingObjsList;
    std::vector<StaticObjects *> staticObjsList;

    unsigned int gameWidgetHeight;
    unsigned int gameWidgetWidth;

    GameStages currStage;
    TileMap tileMap;

    std::map<int,GameStages> menuInTitle;
    unsigned int titleCoice;
};


#endif // GAMESTATE_H
