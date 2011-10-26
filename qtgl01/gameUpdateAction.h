#ifndef GAMEUPDATEACTION_H
#define GAMEUPDATEACTION_H

#include"gamestate.h"


class gameUpdateAction
{
public:


    static void renderingMaps(GameState& );
    static void renderingPlayers(GameState&);
    static void renderingEnemies(GameState&);

};

#endif // GAMEUPDATEACTION_H
