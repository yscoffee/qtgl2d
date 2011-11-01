#ifndef FLOORS_H
#define FLOORS_H

#include "objects.h"
#include "movingobjects.h"

class Floors: public Objects
{
public:
    Floors();

    //no need update
    virtual void update(const long ){}
    virtual void rendering();

    bool encounterFloor(MovingObjects& );
protected:



};

#endif // FLOORS_H
