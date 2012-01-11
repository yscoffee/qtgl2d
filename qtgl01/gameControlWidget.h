#ifndef gameControlWidget_H
#define gameControlWidget_H

#include <QGLWidget>
#include "runnable.h"
#include "gamemode.h"

namespace Ui {
    class GameControlWidget;
}


class GameControlWidget : public QGLWidget
{
    Q_OBJECT

private :
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

    //GameStateMaintainer gameState;

    Runnable * currHandler;
    TitleMode tiltMode;
    GameMode gameMode;

    void initialGameState();


private slots:
    void startIdleFunc();
};

#endif
