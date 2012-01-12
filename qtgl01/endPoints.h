#ifndef ENDPOINTS_H
#define ENDPOINTS_H

#include "staticobjects.h"
#include "drawutilities.h"
#include "textures.h"

class EndPoints:public StaticObjects
{
private:
    static Textures tex;

public:
    EndPoints(const int X,const int Y, const int Z):StaticObjects(X,Y,Z){}
    virtual void rendering()const{
        DrawUtilities::drawSquareWithTexture(x,y,z,LENGTH,tex.getTID());
    }

    static const int LENGTH=40;
    static void initTexture();
};



#endif // ENDPOINT_H
