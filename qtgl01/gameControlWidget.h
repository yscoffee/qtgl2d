#ifndef gameControlWidget_H
#define gameControlWidget_H

#include <QGLWidget>
#include "runnable.h"
#include "gamemode.h"
#include "titlemode.h"
#include "scoreboardmode.h"

namespace Ui {
    class GameControlWidget;
}


class GameControlWidget : public QGLWidget
{
    Q_OBJECT


public:
    explicit GameControlWidget(QWidget *parent = 0);
    ~GameControlWidget();
    enum GameStages{ GS_TitleMode , GS_GameMode, GS_Pasted, GS_ScoreBoard ,GS_GameEnd };

    void initializeGL();
    //reshape
    void resizeGL(int width, int height);
    //display
    //call by updateGL()
    void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *);
    void drawAxs();
    void switchMode(const GameStages);

private:


    static const int IDLE_REDRAW_MS=10;
    int redrawTimerID;

    Ui::GameControlWidget *ui;



    Runnable * currHandler;
    TitleMode tiltMode;
    GameMode gameMode;
    ScoreBoardMode scoreboardMode;
    void initialGameState();


private slots:
    void startIdleFunc();
};

#endif
