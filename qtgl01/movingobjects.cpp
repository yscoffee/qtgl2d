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
void MovingObjects::setAccX(const int AX){ ax=AX;}
void MovingObjects::setAccY(const int AY){ ay=AY;}
void MovingObjects::setAccZ(const int AZ){ az=AZ;}


int MovingObjects::getX(){return x;}
int MovingObjects::getY(){return y;}
int MovingObjects::getZ(){return z;}
void MovingObjects::setX(const int X){ x=X;}
void MovingObjects::setY(const int Y){ y=Y;}
void MovingObjects::setZ(const int Z){ z=Z;}


int MovingObjects::getVX(){return vx;}
int MovingObjects::getVY(){return vy;}
int MovingObjects::getVZ(){return vz;}
void MovingObjects::setVX(const int VX){ vx=VX;}
void MovingObjects::setVY(const int VY){ vy=VY;}
void MovingObjects::setVZ(const int VZ){ vz=VZ;}
