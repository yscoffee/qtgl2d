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
    enum States{ S_BOTTOM_FLOOR, S_JUMPING ,S_HIGHFLOOR,S_FALL };
    States state;

    float vx;
    float vy;
    float vz;

    //int floorY;
    bool onGround;

public:
    MovingObjects();
    void setState(States);
    virtual States getState();
    inline
    static States getBottomFloorState(){return S_BOTTOM_FLOOR;}
    inline
    static States getJumpingState(){return S_JUMPING;}
    inline
    static States getFallState(){return S_FALL;}
    inline
    static States getHighFloorState(){return S_HIGHFLOOR;}
    static const float MAX_VX=0.4;
    static const float JUMP_SPEED =  0.95f;


    virtual float getVX();
    virtual float getVY();
    virtual float getVZ();
    virtual void setVX(const float);
    virtual void setVY(const float);
    virtual void setVZ(const float);
    //virtual void setfloorY(const int F){floorY=F;}
    virtual void update(const int );

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






