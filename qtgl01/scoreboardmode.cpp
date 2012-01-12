#include "scoreboardmode.h"
#include "gameControlWidget.h"
#include <QGLWidget>
#include <fstream>
#include <algorithm>
#include <cstdio>

ScoreBoardMode::ScoreBoardMode(QGLWidget& P):
    parent(P),font(QFont("MS Gothic",40)),
    smallfont(QFont("MS Gothic",20)),score(0),animateSocre(0),
    scorelist(5,-1),animatIsDone(false),anitRankMs(0),showTopMode(false)
{
}
void ScoreBoardMode::ini()
{
    animateSocre=0;
    anitRankMs=0;
    animatIsDone=false;
    scorelist.clear();
    score=-1;
    std::fstream records("./lastresult.tmp",std::fstream::in);
    records>>score;
    records.close();


    //read all old records
    int input=0;
    records.open("./score.log",std::ios_base::in);
    for(int ix=0; !records.eof() ; ix++){
        if(  records>>input ){
            scorelist.push_back(input);
        }
    }
    records.close();

    //change into DESC order
    std::sort(scorelist.begin(),scorelist.end());
    std::reverse(scorelist.begin(),scorelist.end());

    //Assume there must be a record.
    if(score == -1){
        showTopMode=true;
        score=scorelist[0];
    }else{
        showTopMode=false;
    }
}

void ScoreBoardMode::updateAction(const long & MS)
{
    if( animateSocre < score){
        animateSocre=std::min(1.0*score,animateSocre+0.5);

        anitRankMs+=MS;
    }else{
        animatIsDone=true;
    }

}

void ScoreBoardMode::drawAction()
{
    glColor3f(1,1,1);
    if(showTopMode)
        parent.renderText(parent.width()/2-180,165,QString("Top"),QFont("MS Gothic",10));
    else
        parent.renderText(parent.width()/2-180,165,QString("Last"),QFont("MS Gothic",10));

    parent.renderText(parent.width()/2-150,195,QString("Score:")+QString::number(animateSocre),font);
    parent.renderText(parent.width()/2-160,225,QString("-----------------------------"),smallfont);
    static char rank[30]={0};

    foundRank=false;

    if(animatIsDone){
        for(int ix=0; ix<5 ; ix++){
            if( -1 != scorelist[ix] ){
                if(!foundRank && score == scorelist[ix]){
                    glColor3d(0,0.2,1);
                    foundRank=true;
                }else
                   glColor3f(1,1,1);
                memset(rank,0,sizeof(rank));
                sprintf(rank,"Rank %2d : %3d\n",ix+1,scorelist[ix] );
                parent.renderText(parent.width()/2-110,250+40*ix,QString(rank),smallfont);
            }else{
                sprintf(rank,"Rank %2d : N.A.\n",ix+1);
                parent.renderText(parent.width()/2-110,250+40*ix,QString(rank),smallfont);
            }
        }
        /*show color
        if(!showTopMode){

            std::vector<int>::iterator iter = find (myvector.begin(), myvector.end(), score);
            int index = iter - myvector.begin();
            memset(rank,0,sizeof(rank));
            sprintf(rank,"Rank XX : %3d\n",score );
            parent.renderText(parent.width()/2-110,250+40*5,QString(rank),smallfont);
        }*/

        parent.renderText(parent.width()/2-150,520,QString("press Enter to exit..."),QFont("MS Gothic",10));
    }else{
        for(int ix=0; ix< std::min(5,anitRankMs/100) ; ix++){
            memset(rank,0,sizeof(rank));
            if( -1!= scorelist[ix] ){
                sprintf(rank,"Rank %2d : %3d\n",ix+1,scorelist[ix] );
                parent.renderText(parent.width()/2-110,250+40*ix,QString(rank),smallfont);
            }else{
                sprintf(rank,"Rank %2d : N.A.\n",ix+1);
                parent.renderText(parent.width()/2-110,250+40*ix,QString(rank),smallfont);
            }
        }

    }

}

void ScoreBoardMode::keyPress(const int &K)
{
    if(  K == Qt::Key_Return ){
        endclear();
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

void ScoreBoardMode::endclear()
{
    std::fstream records("./lastresult.tmp",std::fstream::out);
    records<<-1;
    records.close();
}

