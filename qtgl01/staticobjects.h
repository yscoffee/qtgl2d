#ifndef STATICOBJECTS_H
#define STATICOBJECTS_H

#include "objects.h"

class StaticObjects : public Objects
{
protected:

public:

    StaticObjects(const int X=0, const int Y=0,const int Z=0):Objects(X,Y,Z){}
    virtual void rendering()const;
    virtual void update(const int );

    virtual int getWidth();
    virtual int getHeight();


};

#endif // STATICOBJECTS_H
