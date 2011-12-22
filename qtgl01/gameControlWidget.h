#ifndef gameControlWidget_H
#define gameControlWidget_H

#include <QGLWidget>
#include <qgl.h>
#include "gameStateMaintainer.h"
#include "gameupdateaction.h"

namespace Ui {
    class GameControlWidget;
}

class GameControlWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GameControlWidget(QWidget *parent = 0);
    ~GameControlWidget();

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
private:

    static const int IDLE_REDRAW_MS=10;

    Ui::GameControlWidget *ui;
    int redrawTimerID;

    GLdouble trafX;
    GLdouble trafY;
    GLdouble trafZ;

    GameStateMaintainer gameState;

    void draw();
    void initialGameState();


private slots:
    void startIdleFunc();
};

#endif
