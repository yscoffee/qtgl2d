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

    virtual inline int getX();
    virtual inline int getY();
    virtual inline int getZ();
    virtual inline void setX(const int);
    virtual inline void setY(const int);
    virtual inline void setZ(const int);


    virtual inline int getVX();
    virtual inline int getVY();
    virtual inline int getVZ();
    virtual inline void setVX(const int);
    virtual inline void setVY(const int);
    virtual inline void setVZ(const int);

    virtual inline int getAccX();
    virtual inline int getAccY();
    virtual inline int getAccZ();
    virtual inline void setAccX(const int);
    virtual inline void setAccY(const int);
    virtual inline void setAccZ(const int);
    virtual void rendering()=0;

};

#endif // MOVINGOBJECTS_H
