#ifndef PLAYERS_H
#define PLAYERS_H

#include "movingobjects.h"
#include <QGLWidget>

class Players: public MovingObjects
{
private:

    double hp;
    double mp;
    double sp;
    double exp;
    int level;

    const int HALF_WID;
    const int HALF_HEI;
    GLint vertices[8][3];

public:
    Players();

    virtual void rendering();
    static void renderPlayerInfos(const Players&);


};

#endif // PLAYERS_H
