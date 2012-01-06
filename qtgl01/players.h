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

    double hp;
    double mp;
    double sp;
    double exp;
    int level;

    const int HALF_WID;
    const int HALF_HEI;
    GLint vertices[8][3];

    int preX;
    int preY;
    int preZ;

public:

    int scores;
    static void renderPlayerInfos(const int SX, const int SY,QGLWidget *,Players&);
    static void initTexture();
    Players();
    void resetState();
    virtual void rendering();
    virtual void update(const int MS);
    virtual int getHeight(){return 2*HALF_HEI;}
    virtual int getWidth(){return 2*HALF_WID;}
    inline
    int getHalfWidth(){return HALF_WID;}
    inline
    int getHalfHeight(){return HALF_HEI;}

    //int getFloorY(){return floorY;}
    void handleCollision(  Objects*);
    void performFalling(const long MS);
};

#endif // PLAYERS_H
