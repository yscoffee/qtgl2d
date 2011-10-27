#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "players.h"
#include "movingobjects.h"
#include <QtEvents>

class GameState
{
public:

    GameState(const unsigned int WIDTH, const unsigned int HEIGHT);
    void updateLocation();
    void renderLiveObjs();
    void addLiveObj(MovingObjects *);
    void keyboardMovingAction(const QKeyEvent *);
    void setGameWidgetHeight(const unsigned int );
    void setGameWidgetWidth(const unsigned int );
private:

    Players& play1;
    std::vector<MovingObjects *> liveObjs;

    unsigned int gameWidgetHeight;
    unsigned int gameWidgetWidth;
};

#endif // GAMESTATE_H
