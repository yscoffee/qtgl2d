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

    //central point
    int x;
    int y;
    int z;

    //velocity
    int vx;
    int vy;
    int vz;

    //acceleration
    int ax;
    int ay;
    int az;

    //F = MA
    //Time
    unsigned int fT;

    // F/M = A
    double fx;
    double fy;
    double fz;

    double m;

public:
    MovingObjects();
    void setState(States);
    States getState();
    inline
    static States getNormalState(){return S_NORMAL;}
    inline
    static States getJumpingState(){return S_JUMPING;}

    virtual int getX();
    virtual int getY();
    virtual int getZ();
    virtual void setX(const int);
    virtual void setY(const int);
    virtual void setZ(const int);

    virtual int getVX();
    virtual int getVY();
    virtual int getVZ();
    virtual void setVX(const int);
    virtual void setVY(const int);
    virtual void setVZ(const int);

    virtual int getAccX();
    virtual int getAccY();
    virtual int getAccZ();
    virtual void setAccX(const int);
    virtual void setAccY(const int);
    virtual void setAccZ(const int);

    virtual void update(const long ELAPSED_MS );

};

#endif // MOVINGOBJECTS_H






