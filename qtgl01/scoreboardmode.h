#ifndef SCOREBOARDMODE_H
#define SCOREBOARDMODE_H


#include "runnable.h"
#include <QGLWidget>
#include <vector>

class ScoreBoardMode : public Runnable
{
private :
    QGLWidget& parent;
    int score;
    int anitRankMs;
    double animateSocre;
    bool foundRank;

    QFont font;
    QFont smallfont;
    std::vector<int> scorelist;
    bool animatIsDone;
    bool showTopMode;


public:
    ScoreBoardMode(QGLWidget& P);

    void setScore(const int&);

    virtual void ini();

    virtual void updateAction(const long&);
    virtual void drawAction(void);
    void endclear();
    virtual void keyPress(const int &);
    virtual void keyRelease(const int &);
};

#endif // SCOREBOARDMODE_H
