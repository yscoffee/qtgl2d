#include "floors.h"

Floors::Floors()
{
}

bool Floors::encounterFloor(MovingObjects &obj)
{
    //assume currently floor is a plane with y=1;
    return obj.getY()!=0;
}

void Floors::rendering()
{
}
