#ifndef OBJECTS_H
#define OBJECTS_H
#include <string>
class Objects
{
protected:
   std::string name;
   //central point
   int x;
   int y;
   int z;

public:
    Objects(const int X=0,const int Y=0,const int Z=0);

    virtual void rendering()const=0;
    //Call by Timer. Be used to update state of game object
    //Unit of time is millisecond second
    virtual void update(const int )=0;

    virtual int getWidth()=0;
    virtual int getHeight()=0;

    inline
    int getX(){return x;}
    inline
    int getY(){return y;}
    inline
    int getZ(){return z;}

    inline
    void setX(const int X){ x=X; }
    inline
    void setY(const int Y){ y=Y; }
    inline
    void setZ(const int Z){ z=Z; }


};

#endif // OBJECTS_H
