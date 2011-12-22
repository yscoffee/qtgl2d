#include "stars.h"
#include <objects.h>

Textures Stars::tex;

Stars::Stars(const int X,const int Y, const int Z):Objects(X,Y,Z)
{
}

void Stars::initTexture()
{
    Stars::tex.initial("..\\textures\\star.png");
}
