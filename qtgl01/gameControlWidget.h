#ifndef gameControlWidget_H
#define gameControlWidget_H

#include <QGLWidget>
#include "gamestate.h"
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
    void paintGL();
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *);
    void drawAxs();
private:
    Ui::GameControlWidget *ui;

    void draw();
    void draw3DSquare();
    bool deBugON;

    int redrawTimerID;

    GLdouble trafX;
    GLdouble trafY;
    GLdouble trafZ;
    //theta is the angle of axis rotation
    GLdouble rotaTheta[3];

    GameState gameState;

private slots:
    void startIdleFunc();
};

#endif
