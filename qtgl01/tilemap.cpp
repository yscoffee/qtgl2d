#include "tilemap.h"
#include "floors.h"
#include "debugtools.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "stars.h"
#include <algorithm>
TileMap::TileMap( ):width(0),height(0)
{


}

//@throw: const string, represent invalid map script;
void TileMap::loadMap(const char *path)
{
    std::cout<<"Loading map script:"<<path<<std::endl;
    std::fstream fin(path);
    if(fin.fail()){
        std::cerr<<"open failed";
         throw('open failed.');
    }
    std::string line;

    height=0;
    width=0;
    //load map script
    //reading map from heighest line to lowest line
    while(getline(fin,line)){


        width=(width<line.size())?line.size():width;
        std::vector<int> newLine;

        //skip a comment line.
        if( line.size() && line[0] =='#' )
            continue;
        else{
        //normal condition
             height++;
            //read in each line
            //and trandform char to pre defined int value
            for(int ix=0 ; ix<line.size() ; ix++){
                if( line[ix]!='\n'){
                    switch(line[ix]){
                        case 'E':
                            newLine.push_back(T_Enemy);break;
                        case '*':
                            newLine.push_back(T_Star);break;
                        case '=':
                            newLine.push_back(T_Floor);break;
                        case ' ':
                            newLine.push_back(T_Transparent);break;
                        case '\t' :
                            std::cerr<<"*ERROR Detect \t."<<std::endl;
                        default:
                            std::cerr<<"*Detect undefined block."<<std::endl;
                            throw('err');
                    }
                }
            }
            map.push_back(newLine);
        }
    }


    //normalize
    //fill space on each line to keep same width of map
    for(int i=0; i<map.size();i++){
        if( map[i].size() <width ){
            while( width - map[i].size() > 0){
                map[i].push_back(T_Transparent);
            }
        }
    }

    //reverse for y[0] mapping y<0>
    std::reverse( map.begin(),map.end());

}

void TileMap::printTileMap()
{
    std::cout<<width<<':'<<height<<std::endl;

    for(int ix=0; ix<map.size();ix++){
        for(int iy=0; iy<map[ix].size();iy++){
            std::cout<<map[ix][iy];
        }
        std::cout<<std::endl;
    }
}

int TileMap::tileToPixels(const unsigned int COORD)
{
    return COORD*TileMap::TILE_SIZE;
}


void TileMap::setupTileMap(){

    for(int iy=0; iy<map.size();iy++){
        for(int ix=0; ix<map[iy].size();ix++){
            switch(map[iy][ix]){
                case T_Floor:
                    addFloor( map2World_X(ix), map2World_Y(iy) , Z_VAL );
                    break;
                case T_Enemy:
                    //addEnemy(map2World_X(ix),map2World_Y(height-iy),Z_VAL);
                    break;
                case T_Star:
                    addStar(map2World_X(ix),map2World_Y(iy),Z_VAL);
                    break;
                case T_Transparent:
                    //do nothings.
                    break;
                default:
                    std::cerr<<"*Detect undefined block."<<std::endl;
                    throw('err');
            }
        }
    }
}

//Parse tile map to real pixel map.
void TileMap::parseMap(const char* path ){

    loadMap(path);
    setupTileMap();


#ifdef __MY_DEBUGS
    printTileMap();
    printObjLists();
#endif
}


void TileMap::addFloor(const int X, const int Y, const int Z)
{

    floorList.push_back(Floors(X,Y,Z,TILE_SIZE,TILE_SIZE));
}

void TileMap::addEnemy(const int, const int, const int)
{
}

void TileMap::addStar(const int X, const int Y, const int Z)
{
    starList.push_back(Stars(X,Y,Z));
}

void TileMap::renderingMap(const int X , const int Y , const int Z, const int SW, const int SH)
{

    for(int ix=0; ix<floorList.size() ; ix++){
        floorList[ix].rendering();
    }
}

void TileMap::printObjLists()
{
    for(int ix=0; ix<floorList.size() ; ix++){
        std::cout<<ix<<"-th:  "<<floorList[ix].getX()<<' '
                <<floorList[ix].getY()<<' '
               <<floorList[ix].getZ()<<' '<<std::endl;
    }
}
bool TileMap::hasAObjInMap(const int X,const int Y){

    int ix = static_cast<int>(floor(X/TILE_SIZE));
    int iy = static_cast<int>(floor(Y/TILE_SIZE));

    if( map[iy][ix] == T_Floor )
        return true;
    else
        return false;
}
bool TileMap::isCollided(const int X, const int Y,const int HWID,const int HHEI){

    //Use to generate 4 bounding points
    int cof[2] = {1,-1};

    //test 4 bounding points
    for(int ix=0; ix < 2 ; ix++){
        for(int iy=0; iy < 2 ; iy++){
            if( hasAObjInMap( X+cof[ix]*HWID , Y+cof[iy]*HHEI ) ){
               return true;
            }
        }
    }




    return false;
}
void TileMap::tileCollisionCheck(Players & player )
{
    int x=player.preX;
    int y=player.preY;
    int x2=player.getX();
    int y2=player.getY();

    if(x==x2 && y==y2)
        return;

    //test x2,y2 is ok or not
    if( isCollided(x2,y2,player.getHalfWidth(),player.getHalfHeight()) ){

        //found collision, test x,y+dy first.
        if( isCollided(x,y2,player.getHalfWidth(),player.getHalfHeight()) ){

            //align to < x2, y' >
            if(y2-y>=0)
                y = map2World_Y(world2Map_Y(y2+player.getHalfHeight()))-TILE_SIZE/2-player.getHalfHeight()-1;
            else
                y = map2World_Y(world2Map_Y(y2-player.getHalfHeight()))+TILE_SIZE/2+player.getHalfHeight()+1;

            player.setY(y);

            player.setVY(0);

            //Re-test
            tileCollisionCheck(player);

        }else{
        //test X-axis, < x+dx,y >
            if( isCollided(x2,y,player.getHalfWidth(),player.getHalfHeight())){
                //align to < x', y+dy>

                if(x2-x>=0)
                    x = map2World_X(world2Map_X(x2+player.getHalfWidth()))-TILE_SIZE/2-player.getHalfWidth()-1;
                else
                    x = map2World_X(world2Map_X(x2-player.getHalfWidth()))+TILE_SIZE/2+player.getHalfWidth()+1;

                player.setX(x);

                player.setVX(0);
                //re-Test
                tileCollisionCheck(player);
            }
        }


    }else
        return;

}
bool  TileMap::starsCollisionCheck(const int X, const int Y, const int W, const int H)
{
    int xDis=0;
    int yDis=0;

    for(int ix=0; ix<starList.size() ; ix++){
        //check X,Y
        xDis = std::abs(static_cast<float>(X-starList[ix].getX()) );
        yDis = std::abs(static_cast<float>(Y-starList[ix].getY()) );

        if(xDis < W/2+starList[ix].getWidth()/2 && yDis < H/2+starList[ix].getHeight()/2 ){
            starList.erase(starList.begin()+ix );
            return true;
        }
    }

    return false;
}
bool TileMap::checkFalling(Players &p1)
{

    int xDis=0;
    int yDis=0;

    for(int ix=0; ix<floorList.size() ; ix++){
        //check X,Y
        xDis = std::abs(static_cast<float>(p1.getX()-floorList[ix].getX()) );
        yDis = std::abs(static_cast<float>(p1.getY()-floorList[ix].getY()) );

        if(xDis < p1.getHalfWidth()+TILE_SIZE/2 &&yDis == p1.getHalfHeight()+TILE_SIZE/2 ){
            return false;
        }
    }

    return true;
}

void TileMap::renderingStars(const int X, const int Y, const int Z, const int SW, const int SH, QGLWidget *p)
{
    for(int ix=0; ix<starList.size() ; ix++){
        starList[ix].rendering(p);
    }
}

