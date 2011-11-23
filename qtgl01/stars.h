#ifndef STARS_H
#define STARS_H

class Stars : public Objects
{
public:
    Stars();
    virtual void rendering(){}//do redering in other side. temp design

    //Call by Timer. Be used to update state of game object
    //Unit of time is millisecond second
    virtual void update(const int ){}
    static const int LENGTH = 5;
    virtual int getWidth(){return LENGTH;}
    virtual int getHeight(){return LENGTH;}
};

#endif // STARTS_H
