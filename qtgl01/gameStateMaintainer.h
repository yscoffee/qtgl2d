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

class GameStateMaintainer
{

private:
    enum GameStages{ GS_Title , GS_Gaming, GS_Pasted, GS_ScoreBoard ,GS_GameEnd };

public:
    GameStateMaintainer(const unsigned int WIDTH, const unsigned int HEIGHT);

    void renderLiveObjs();
    void renderFloors();

    void rendering();

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


    int playerTrans_Y;

    Players& play1;
    Floors floor;

    std::vector<MovingObjects *> movingObjsList;
    std::vector<StaticObjects *> staticObjsList;

    unsigned int gameWidgetHeight;
    unsigned int gameWidgetWidth;

    GameStages currStage;
    TileMap tileMap;


};


#endif // GAMESTATE_H
