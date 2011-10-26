#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

class MovingObject
{

protected:

    int x;
    int y;
    int z;
    int vx;
    int vy;
    int vz;
    int ax;
    int ay;
    int az;

public:
    MovingObject();

    virtual int getX();
    virtual int getY();
    virtual int getZ();
    virtual int getVX();
    virtual int getVY();
    virtual int getVZ();
    virtual int getAccX();
    virtual int getAccY();
    virtual int getAccZ();

};

#endif // MOVINGOBJECT_H
