#ifndef PLAYERS_H
#define PLAYERS_H

#include "movingobjects.h"
#include "textures.h"
#include <QGLWidget>


class Players: public MovingObjects
{
private:

    friend class TileMap;

    //hold texture, should be initialed IN function glInitial()
    static Textures rightModeTex;
    static Textures leftModeTex;
    static Textures fallRModeTex;
    static Textures fallLModeTex;

    double hp;
    double mp;
    double sp;
    double exp;
    int level;

    int halfWidth;
    int halfHeight;
    GLint vertices[8][3];

public:
    int preX;
    int preY;
    int preZ;
    int scores;

    static void renderPlayerInfos(const int SX, const int SY,QGLWidget *,Players&);
    static void initTexture();

    Players();

    void resetState();
    void setHalfWid(const int HW){halfWidth=HW;}
    virtual void rendering()const;
    virtual void update(const int MS);
    virtual int getHeight(){return 2*halfHeight;}
    virtual int getWidth(){return 2*halfWidth;}
    inline
    int getHalfWidth(){return halfWidth;}
    inline
    int getHalfHeight(){return halfHeight;}
    void jump();
    //int getFloorY(){return floorY;}
    //void handleCollision(  Objects*);
    //void performFalling(const long MS);
};

#endif // PLAYERS_H
