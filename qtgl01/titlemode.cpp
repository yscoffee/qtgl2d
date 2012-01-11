#include "titlemode.h"
#include "gameControlWidget.h"

void TitleMode::ini(){
    titleChoice=0;

}
void TitleMode::updateAction(const long&){}
void TitleMode::drawAction(void){
        glColor3f(1,1,1);
       // window coordinates
       // with the origin in the upper left-hand corner of the window

       parent.renderText(parent.width()/3,parent.height()/4,QString("JJJJJump!"),headFont);
       //render menu

       static int dx = parent.width()*2/5;
       static int dy = parent.height()/2;
       static QString gs = QString(">  Game Start");
       static QString sb = QString(">  Score Board");
       static QString exit = QString(">  Exit");

       glColor3f(0.5,0.5,0.5);
       parent.renderText(dx,dy,gs,listFont);
       parent.renderText(dx,dy+40,sb,listFont);
       parent.renderText(dx,dy+80,exit,listFont);

       glColor3d(0,0,1);
       //parent->renderText(dx,dy+titleCoice*40,QString(">"),listFont);
       switch(titleChoice){
           case 0:
               parent.renderText(dx,dy,gs,listFont);
               break;
           case 1:
               parent.renderText(dx,dy+40,sb,listFont);
               break;
           case 2:
               parent.renderText(dx,dy+80,exit,listFont);
               break;
           default:
           break;
       }
}
void TitleMode::keyPress(const int &K){
    if( K == Qt::Key_Down ){
        titleChoice=std::min(2,(++titleChoice));
    }else if( K == Qt::Key_Up ){
        titleChoice=std::max(0,(--titleChoice));

    }else if( K == Qt::Key_Return || K == Qt::Key_Space ){
        // when pass ENTER & SPACE
        //enter new state
        switch(titleChoice){
            case 0 :
                //game start
                static_cast<GameControlWidget&>(parent).switchMode( GameControlWidget::GS_GameMode );
                break;
            case 1 :
                static_cast<GameControlWidget&>(parent).switchMode( GameControlWidget::GS_ScoreBoard );
                break;
            case 2 :
                static_cast<GameControlWidget&>(parent).switchMode( GameControlWidget::GS_End );
                break;
            default: break;
        }
    }
}

void TitleMode::keyRelease(const int &K){

}

TitleMode::TitleMode(QGLWidget& GCW):
    titleChoice(0),parent(GCW),headFont(QFont("Georgia",50)),listFont(QFont("Georgia",20))
{



}
