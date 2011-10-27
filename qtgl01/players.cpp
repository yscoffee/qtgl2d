#include "players.h"
#include "movingobjects.h"

#include <QGLWidget>

Players::Players():
    hp(0),mp(0),sp(0),exp(0),level(0)
{



}

void Players::rendering(){

    glBegin(GL_POLYGON);

    glEnd();

}

