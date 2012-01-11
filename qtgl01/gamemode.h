#ifndef GAMEMODE_H
#define GAMEMODE_H
#include "runnable.h"
#include "movingobjects.h"
#include "players.h"
#include "drawutilities.h"
#include "tilemap.h"
#include "floors.h"

#include <cmath>
#include <QGLWidget>


class GameMode : public Runnable
{
private :
    QGLWidget& parent;
    TileMap tileMap;
    int playerTrans_Y;

    Players& play1;
    Floors floor;

    std::vector<MovingObjects *> movingObjsList;
    void renderLiveObjs();

    int getScrXOffset(const int S_WID){
#ifdef __MY_DEBUGS
        static int c=0;c++;
#endif
        if( play1.getX()+S_WID/2 > tileMap.getMapWorldCoordWidth() ){
#ifdef __MY_DEBUGS
            std::cout<<"TX"<<c<<' '<<-1*(tileMap.getMapWidth() - S_WID )<<std::endl;
#endif
            return -1*std::abs(static_cast<float>(tileMap.getMapWorldCoordWidth() - S_WID ));

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


    inline
    int getMapWidth(){return tileMap.getMapWorldCoordWidth();}
    inline
    int getMapHeight(){return tileMap.getMapWorldCoordHeight();}
    inline
    int getPlayerX(){return play1.getX();}
    inline
    int getPlayerY(){return play1.getY();}
    inline
    void addMovingObj(MovingObjects *newObj){
      movingObjsList.push_back(newObj);
    }
    inline
    void resetPlayer(){ play1.resetState();}

public:
    GameMode(QGLWidget& P);
    virtual void ini();

    virtual void updateAction(const long&);
    virtual void drawAction(void);

    virtual void keyPress(const int &);
    virtual void keyRelease(const int &);

};

#endif // GAMEMODE_H
