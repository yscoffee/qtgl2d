#ifndef FLOORS_H
#define FLOORS_H

#include "objects.h"
#include "movingobjects.h"

class Floors: public Objects
{
public:
    Floors();
    Floors(const int X,const int Y,const int Z,const unsigned int W=FLOOR_LEN,const unsigned int L=FLOOR_LEN);

    //no need update
    virtual void update(const long ){}
    virtual void rendering();

    bool encounterFloor(MovingObjects& );

    static const unsigned int FLOOR_LEN=2;

protected:
    unsigned int width;
    unsigned int height;

};

#endif // FLOORS_H
