#ifndef MOVINGOBJECTS_H
#define MOVINGOBJECTS_H

class MovingObjects
{

protected:

    //central point
    int x;
    int y;
    int z;

    //velocity
    int vx;
    int vy;
    int vz;
    int ax;
    int ay;
    int az;

public:
    MovingObjects();

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

    virtual void rendering()=0;

};

#endif // MOVINGOBJECTS_H
