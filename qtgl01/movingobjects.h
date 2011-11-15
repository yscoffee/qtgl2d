#ifndef MOVINGOBJECTS_H
#define MOVINGOBJECTS_H

#include "objects.h"
/*
 *
 * Note that the units of time of MovingObjects is millisecond.
 * meter(metre) = pixel
 *
 */

class MovingObjects : public Objects
{

protected:
    enum States{ S_NORMAL, S_JUMPING };
    States state;

    float vx;
    float vy;
    float vz;

    int floorY;
    bool onGround;

public:
    MovingObjects();
    void setState(States);
    States getState();
    inline
    static States getNormalState(){return S_NORMAL;}
    inline
    static States getJumpingState(){return S_JUMPING;}

    static const float MAX_VX=0.4;
    static const float JUMP_SPEED =  0.95f;


    virtual float getVX();
    virtual float getVY();
    virtual float getVZ();
    virtual void setVX(const float);
    virtual void setVY(const float);
    virtual void setVZ(const float);
    virtual void setfloorY(const int F){floorY=F;}
    virtual void update(const int ELAPSED_MS );

    virtual void jump();

    void collideHorizontal(){
        setVX(0);
    }

    void collideVertical() {
        if (getVY() > 0) {
            onGround = true;
        }
        setVY(0);
    }

};

#endif // MOVINGOBJECTS_H






