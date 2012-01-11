#ifndef TITLEMODE_H
#define TITLEMODE_H

#include"runnable.h"
#include<QGLWidget>

class TitleMode : public Runnable
{
private :
    int titleChoice;
    QGLWidget& parent;
    QFont headFont;
    QFont listFont;
public:
    TitleMode(QGLWidget& GCW);
    virtual void ini();

    virtual void updateAction(const long&);
    virtual void drawAction(void);

    virtual void keyPress(const int &);
    virtual void keyRelease(const int &);

};


#endif // TITLEMODE_H
