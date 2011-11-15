#ifndef PLAYERS_H
#define PLAYERS_H

#include "movingobjects.h"

#include <QGLWidget>

class Players: public MovingObjects
{
private:

    double hp;
    double mp;
    double sp;
    double exp;
    int level;

    const int HALF_WID;
    const int HALF_HEI;
    GLint vertices[8][3];

public:

    static void renderPlayerInfos(const Players&);

    Players();
    void resetState();
    virtual void rendering();
    virtual void update(const long MS);
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
