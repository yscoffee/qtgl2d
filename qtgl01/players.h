#ifndef PLAYERS_H
#define PLAYERS_H
#include "movingobjects.h"
class Players: public MovingObjects
{
private:

    double hp;
    double mp;
    double sp;
    double exp;
    int level;

public:
    Players();

    void rendering();
};

#endif // PLAYERS_H
