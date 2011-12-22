#ifndef FLOORS_H
#define FLOORS_H

#include "objects.h"
#include "movingobjects.h"
#include "textures.h"
class Floors: public Objects
{
public:
    Floors();
    ~Floors();
    Floors(const int X,const int Y,const int Z,const unsigned int W,const unsigned int L);

    //no need update
    virtual void update(const int ){}
    virtual void rendering();
    virtual int getWidth(){return width;}
    virtual int getHeight(){return height;}

    bool encounterFloor(MovingObjects& );

   // static const unsigned int DEF_FLOOR_LEN=10;
    static void initTexture(const char*);

protected:
    unsigned int width;
    unsigned int height;
    virtual void bindTexture(){}
private:
    static Textures tex;


};

#endif // FLOORS_H
