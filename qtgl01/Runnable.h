#ifndef RUNNABLE_H
#define RUNNABLE_H


//abstract base
class Runnable{

public:

    virtual void ini()=0;

    virtual void updateAction(const long&)=0;
    virtual void drawAction(void)=0;

    virtual void keyPress(const int &){}
    virtual void keyRelease(const int &){}
};


#endif // RUNNABLE_H
