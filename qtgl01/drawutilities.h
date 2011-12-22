#ifndef DRAWUTILITIES_H
#define DRAWUTILITIES_H
#include <QtOpenGL>

class DrawUtilities
{
public:
    DrawUtilities();

    //use x,y,z to be the central point of square
    static void draw3DSquare(const int X ,const int Y,const int Z, const int L);
    static void drawSquareWithTexture(const int X, const int Y, const int Z, const int L ,const GLuint TID);

};

#endif // DRAWUTILITIES_H
