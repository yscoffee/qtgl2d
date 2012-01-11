#include "scoreboardmode.h"
#include "gameControlWidget.h"
#include <QGLWidget>

ScoreBoardMode::ScoreBoardMode(QGLWidget& P):parent(P),font(QFont("Georgia",40)),smallfont(QFont("Georgia",10)),score(0)
{

}
void ScoreBoardMode::ini()
{
    score=0;
}

void ScoreBoardMode::updateAction(const long & MS)
{
}

void ScoreBoardMode::drawAction()
{
    parent.renderText(parent.width()/3,parent.height()/4,QString("Score :")+QString::number(score),font);
    parent.renderText(parent.width()/4,parent.height()/2,QString("press Enter to exit..."),smallfont);

}

void ScoreBoardMode::keyPress(const int &K)
{
    if(  K == Qt::Key_Return ){

        static_cast<GameControlWidget&>(parent).switchMode(GameControlWidget::GS_TitleMode);

    }
}

void ScoreBoardMode::keyRelease(const int &)
{
}

void ScoreBoardMode::setScore(const int& s)
{
    score =s;
}

