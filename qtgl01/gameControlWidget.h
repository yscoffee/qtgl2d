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
    void mouseMoveEvent(QMouseEvent *event);
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
    //theta is the angle of axis rotation
    GLdouble rotaTheta[3];
    GameStateMaintainer gameState;

    void draw();
    void draw3DSquare();
    void draw3DSquare(const int,const int,const int, const int );
    void initialGameState();

    //----------------------------------------
    //trackball vars & funcs
    double angle;
    double axis[3];
    double lastPos[3];
    bool trackingMouse;
    int lastX;
    int lastY;

    void startMotion(const int,const int);
    void stopMotion(const int,const int);
    void trackball_ptov(int x, int y, int width, int height, double v[3]);

private slots:
    void startIdleFunc();
};

#endif
