#ifndef PLAYERS_H
#define PLAYERS_H

class Players:public MovingObjects
{
private:

    double hp;
    double mp;
    double sp;
    double exp;
    int level;

public:
    Players();
};

#endif // PLAYERS_H
