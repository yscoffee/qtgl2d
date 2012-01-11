#ifndef SCOREBOARDMODE_H
#define SCOREBOARDMODE_H


#include "runnable.h"
#include <QGLWidget>

class ScoreBoardMode : public Runnable
{
private :
    QGLWidget& parent;
    int score;
    QFont font;
    QFont smallfont;

public:
    ScoreBoardMode(QGLWidget& P);

    void setScore(const int&);

    virtual void ini();

    virtual void updateAction(const long&);
    virtual void drawAction(void);

    virtual void keyPress(const int &);
    virtual void keyRelease(const int &);
};

#endif // SCOREBOARDMODE_H
