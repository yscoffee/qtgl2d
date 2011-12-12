#ifndef STATICOBJECTS_H
#define STATICOBJECTS_H

#include "objects.h"

class StaticObjects : public Objects
{
protected:

public:

    StaticObjects();
    void rendering();
    //Call by Timer. Be used to update state of game object
    //Unit of time is millisecond second
    virtual void update(const int );

    virtual int getWidth();
    virtual int getHeight();


};

#endif // STATICOBJECTS_H
