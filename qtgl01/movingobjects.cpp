#include "movingobjects.h"
#include "debugtools.h"
#include <iostream>
MovingObjects::MovingObjects():
    vx(0),vy(0),vz(0),
    state(MovingObjects::S_BOTTOM_FLOOR)
{
  //  floorY=0;

}

inline
float MovingObjects::getVX(){return vx;}
inline
float MovingObjects::getVY(){return vy;}
inline
float MovingObjects::getVZ(){return vz;}
inline
void MovingObjects::setVX(const float VX){ vx=VX;}
inline
void MovingObjects::setVY(const float VY){ vy=VY;}
inline
void MovingObjects::setVZ(const float VZ){ vz=VZ;}

//Call by Timer. Be used to update state of game object
//Unit of time is micro second
// now it's call at evey 10ms
void MovingObjects::update(const int ELAPSED_MS ){


/*
    if (state == getJumpingState() && getY() <= floorY) {
      setVY(0);
      setY(floorY);
      state = getNormalState();
    }else
 */
    if (state == getJumpingState() || state == getFallState()) {
       setVY(getVY() - 0.002 * ELAPSED_MS);
    }

    // move player
    x += vx * ELAPSED_MS;
    y += vy * ELAPSED_MS;


}

inline
MovingObjects::States MovingObjects::getState()
{
    return state;
}

void MovingObjects::setState(MovingObjects::States S)
{
    state = S;
}


void MovingObjects::jump()
{
    if( state != getJumpingState() && state != getFallState() ){

        state=getJumpingState();
        setVY(JUMP_SPEED);
   }
}



