#ifndef MOVINGOBJECTS_H
#define MOVINGOBJECTS_H

class MovingObjects
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
    MovingObjects();

    virtual int getX();
    virtual int getY();
    virtual int getZ();
    virtual void setX(int);
    virtual void setY(int);
    virtual void setZ(int);


    virtual int getVX();
    virtual int getVY();
    virtual int getVZ();
    virtual void setVX(int);
    virtual void setVY(int);
    virtual void setVZ(int);

    virtual int getAccX();
    virtual int getAccY();
    virtual int getAccZ();
    virtual void setAccX(int);
    virtual void setAccY(int);

    virtual void rendering()=0;

};

#endif // MOVINGOBJECTS_H
