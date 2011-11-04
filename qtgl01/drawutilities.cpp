#include "drawutilities.h"
#include "debugtools.h"
#include <QtOpenGL>
#include <iostream>
DrawUtilities::DrawUtilities()
{
}

void DrawUtilities::draw3DSquare(const int X, const int Y, const int Z, const int L)
{
    const int HL = L/2;
    if(HL==0){
        std::cerr<<"error HL=0";
        throw("error");
    }
    // Set The Color To Blue One Time Only
    glColor3f(0.7f,0.2f,0.8f);

    //X,Y,Z is central point of a 3D box.
    // CCW -defualt mode
    /////////////////////////////////////////////////////////////////////////
    //    v6----- v5
    //   /|      /|
    //  v1------v0|
    //  | |     | |
    //  | |v7---|-|v4
    //  |/      |/
    //  v2------v3
    GLfloat vertices[]={
        X+HL,Y+HL,Z+HL,//v0
        X-HL,Y+HL,Z+HL,//v1
        X-HL,Y-HL,Z+HL,//v2
        X+HL,Y-HL,Z+HL,//v3
        X+HL,Y-HL,Z-HL,//v4
        X+HL,Y+HL,Z-HL,//v5
        X-HL,Y+HL,Z-HL,//v6
        X-HL,Y-HL,Z-HL,//v7
    };
    // color array
    GLfloat colors[] = {1,1,1,  1,1,0,  1,0,0,  1,0,1,              // v0-v1-v2-v3
                        1,1,1,  1,0,1,  0,0,1,  0,1,1,              // v0-v3-v4-v5
                        1,1,1,  0,1,1,  0,1,0,  1,1,0,              // v0-v5-v6-v1
                        1,1,0,  0,1,0,  0,0,0,  1,0,0,              // v1-v6-v7-v2
                        0,0,0,  0,0,1,  1,0,1,  1,0,0,              // v7-v4-v3-v2
                        0,0,1,  0,0,0,  0,1,0,  0,1,1};             // v4-v7-v6-v5

    // index array of vertex array for glDrawElements()
    // Notice the indices are listed straight from beginning to end as exactly
    // same order of vertex array without hopping, because of different normals at
    // a shared vertex. For this case, glDrawArrays() and glDrawElements() have no
    // difference.
    GLubyte indices[] ={ 0,1,2,3,
                         0,3,4,5,
                         0,5,6,1,
                         1,6,7,2,
                         7,4,3,2,
                         4,7,6,5 };

       //glEnableClientState(GL_NORMAL_ARRAY); //Note  flag of lighting sys is turn-off.
       glEnableClientState(GL_COLOR_ARRAY);
       glEnableClientState(GL_VERTEX_ARRAY);

       glColorPointer(3, GL_FLOAT, 0, colors);
       glVertexPointer(3, GL_FLOAT, 0, vertices );
       glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE, indices);

       glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
       glDisableClientState(GL_COLOR_ARRAY);
}
