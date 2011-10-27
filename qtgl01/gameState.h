#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "players.h"
#include "movingobjects.h"
#include <QtEvents>

class GameState
{
public:

    GameState();
    void updateLocation();
    void renderLiveObjs();
    void addLiveObj(MovingObjects *);
    void keyboardMovingAction(const QKeyEvent *);

private:

    Players& play1;
    std::vector<MovingObjects *> liveObjs;

};

#endif // GAMESTATE_H
