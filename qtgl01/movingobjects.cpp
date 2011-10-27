#include "movingobjects.h"

MovingObjects::MovingObjects():
    x(0),y(0),z(0),
    vx(0),vy(0),vz(0),
    ax(0),ay(0),az(0)
{



}

inline
int MovingObjects::getAccX(){return ax;}
inline
int MovingObjects::getAccY(){return ay;}
inline
int MovingObjects::getAccZ(){return az;}
inline
void MovingObjects::setAccX(const int AX){ ax=AX;}
inline
void MovingObjects::setAccY(const int AY){ ay=AY;}
inline
void MovingObjects::setAccZ(const int AZ){ az=AZ;}


inline
int MovingObjects::getX(){return x;}
inline
int MovingObjects::getY(){return y;}
inline
int MovingObjects::getZ(){return z;}
inline
void MovingObjects::setX(const int X){ x=X;}
inline
void MovingObjects::setY(const int Y){ y=Y;}
inline
void MovingObjects::setZ(const int Z){ z=Z;}


inline
int MovingObjects::getVX(){return vx;}
inline
int MovingObjects::getVY(){return vy;}
inline
int MovingObjects::getVZ(){return vz;}
inline
void MovingObjects::setVX(const int VX){ vx=VX;}
inline
void MovingObjects::setVY(const int VY){ vy=VY;}
inline
void MovingObjects::setVZ(const int VZ){ vz=VZ;}
