#include "players.h"
#include "movingobjects.h"

#include <QGLWidget>

Players::Players():
    hp(0),mp(0),sp(0),exp(0),level(0),HALF_WID(4),HALF_HEI(4)
{

/*    for(int ix=0; ix< sizeof(vertices)/sizeof(GLint); ix++){
        vertices[ix][0]=x;
        vertices[ix][1]=y;
        vertices[ix][2]=z;
    }*/
}

void Players::rendering(){

    glBegin(GL_QUADS);
        glColor3d(0,1,0);
        glVertex3d(x+HALF_WID,y+HALF_HEI,z);
        glVertex3d(x-HALF_WID,y+HALF_HEI,z);
        glVertex3d(x-HALF_WID,y-HALF_HEI,z);
        glVertex3d(x+HALF_WID,y-HALF_HEI,z);
    glEnd();


}

void Players::renderPlayerInfos(const Players&)
{


}

void Players::update(const long MS)
{
    MovingObjects::update(MS);

}



