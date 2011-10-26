#include "movingobjects.h"

MovingObjects::MovingObjects():
    x(0),y(0),z(0),
    vx(0),vy(0),vz(0),
    ax(0),ay(0),az(0)
{



}


int MovingObjects::getAccX(){return ax;}
int MovingObjects::getAccY(){return ay;}
int MovingObjects::getAccZ(){return az;}

int MovingObjects::getX(){return x;}
int MovingObjects::getY(){return y;}
int MovingObjects::getZ(){return z;}

int MovingObjects::getVX(){return vx;}
int MovingObjects::getVY(){return vy;}
int MovingObjects::getVZ(){return vz;}
