#include "tilemap.h"
#include "floors.h"
#include "debugtools.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "players.h"
#include "endPoints.h"
#include "stars.h"
#include <algorithm>
#include<map>
TileMap::TileMap( ):width(0),height(0)
{
    start_X=70;
    start_Y=70;
}
TileMap::~TileMap()
{
    clear();
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
                        case 'Q':
                            newLine.push_back(T_EndOfClass);break;
                        case 'S':
                            newLine.push_back(T_BEGIN_LOC);break;
                        case '\t' :
                            std::cerr<<"*ERROR Detect \t."<<std::endl;
                        default:
                            std::cerr<<"*Detect undefined block :"<<line[ix]<<std::endl;
                            //throw('err');
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
    fin.close();
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
                    addFloor( map2World_X(ix), map2World_Y(iy) , Z_VAL ,getTileKey(ix,iy));
                    break;
                case T_Enemy:
                    //addEnemy(map2World_X(ix),map2World_Y(height-iy),Z_VAL);
                    break;
                case T_Star:
                    addStar(map2World_X(ix),map2World_Y(iy),Z_VAL,getTileKey(ix,iy));
                    break;
                case T_Transparent:
                    //do nothings.
                    break;
                case T_EndOfClass:
                    addEndPoint(map2World_X(ix),map2World_Y(iy),Z_VAL,getTileKey(ix,iy));
                    break;
                case T_BEGIN_LOC:
                    start_X=map2World_X(ix);
                    start_Y=map2World_Y(iy);
                    break;
                default:
                    std::cerr<<"*Detect undefined T_{} tags."<<std::endl;
                    throw('e');
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


void TileMap::addFloor(const int X, const int Y, const int Z,const int KEY)
{

    //floorList.push_back(Floors(X,Y,Z,TILE_SIZE,TILE_SIZE));
    floorList.insert(std::pair<int,Floors>(KEY,Floors(X,Y,Z,TILE_SIZE,TILE_SIZE)));

}

void TileMap::addEnemy(const int, const int, const int,const int)
{
}

void TileMap::addStar(const int X, const int Y, const int Z,const int KEY)
{
    //starList.push_back(Stars(X,Y,Z));
    starList.insert(std::pair<int,Stars>(KEY,Stars(X,Y,Z)));
}

void TileMap::renderingMap(const int X , const int Y , const int Z, const int SW, const int SH)
{
    for( std::map<int,Floors>::const_iterator iter=floorList.begin(); iter!=floorList.end() ; iter++){
        (iter->second).rendering();
    }

    for(std::map<int,Stars>::const_iterator iter=starList.begin(); iter!=starList.end() ; iter++){
        (iter->second).rendering();
    }

    for(std::map<int,StaticObjects*>::const_iterator iter = staticObjList.begin() ; iter!=staticObjList.end();iter++ ){
        (iter->second)->rendering();
    }

}
void TileMap::printObjLists()
{
    for(std::map<int,Floors>::iterator iter=floorList.begin(); iter!=floorList.end() ; iter++){
        std::cout<<iter->first<<"-th:  "<<iter->second.getX()<<' '
                 <<iter->second.getY()<<' '
                 <<iter->second.getZ()<<' '<<std::endl;
    }
}
bool TileMap::hasAObjInMap(const int X,const int Y,Players & ply){

    int ix = static_cast<int>(floor(X/TILE_SIZE));
    int iy = static_cast<int>(floor(Y/TILE_SIZE));

    if( map[iy][ix] == T_Floor ){
        //hard collision
        return true;
    }else if( map[iy][ix] == T_Star ){
        //detect soft collision
        removeStar(ix,iy);
        ply.scores++;

        return false;
    }else if( map[iy][ix] == T_EndOfClass ){
        //game end signal
        throw(0);
        return false;
    }else
        return false;
}
bool TileMap::isCollided(const int X, const int Y,const int HWID,const int HHEI,Players& ply){

    //Use to generate 4 bounding points
    int cof[2] = {1,-1};

    //test 4 bounding points
    for(int ix=0; ix < 2 ; ix++){
        for(int iy=0; iy < 2 ; iy++){
            if( hasAObjInMap( X+cof[ix]*HWID , Y+cof[iy]*HHEI , ply ) ){
               return true;
            }
        }
    }
    return false;
}
void TileMap::tileCollisionHandle(Players & player )
{
    int x=player.preX;
    int y=player.preY;
    int x2=player.getX();
    int y2=player.getY();

    if(x==x2 && y==y2)
        return;

    //test x2,y2 is ok or not
    if( isCollided(x2,y2,player.getHalfWidth(),player.getHalfHeight(),player) ){

        //found collision, test x,y+dy first.
        if( isCollided(x,y2,player.getHalfWidth(),player.getHalfHeight(),player) ){

            //align to < x2, y' >
            if(y2-y>=0){
                y = map2World_Y(static_cast<int>((y2+player.getHalfHeight())/TILE_SIZE) )-TILE_SIZE/2-player.getHalfHeight()-0.1;

                if(player.getState()==player.getJumpingState())
                    player.setState(Players::getFallState());
                player.setY(y);
                player.setVY(-player.getVY()*0.45);
            }else{
                y = map2World_Y(static_cast<int>((y2-player.getHalfHeight())/TILE_SIZE))+TILE_SIZE/2+player.getHalfHeight()+0.1;

                if(player.getState()!=Players::getFloorState())
                     player.setState(Players::getFloorState());

                player.setY(y);
                player.setVY(0);
            }

            //Re-test
            tileCollisionHandle(player);

        }else{
        //test X-axis, < x+dx,y >
            if( isCollided(x2,y,player.getHalfWidth(),player.getHalfHeight(),player)){
                //align to < x', y+dy>

                if(x2-x>=0)
                    x = map2World_X(static_cast<int>((x2+player.getHalfWidth())/TILE_SIZE))-TILE_SIZE/2-player.getHalfWidth()-0.1;
                else
                    x = map2World_X(static_cast<int>((x2-player.getHalfWidth())/TILE_SIZE))+TILE_SIZE/2+player.getHalfWidth()+0.1;

                player.setX(x);
                player.setVX(0);
                //re-Test
                tileCollisionHandle(player);
            }
        }

    }else
        return;

}

void TileMap::clear()
{
    width=0;
    height=0;
    start_X=70;
    start_Y=70;

    for(std::map<int,StaticObjects*>::iterator iter = staticObjList.begin() ; iter!=staticObjList.end();iter++ ){
        delete iter->second;
    }
    staticObjList.erase(staticObjList.begin(),staticObjList.end());
    floorList.erase(floorList.begin(),floorList.end());
    starList.erase(starList.begin(),starList.end());

    map.erase(map.begin(),map.end());
    //enemyList.clear();
}

void TileMap::addEndPoint(const int X , const int Y , const int Z,const int KEY)
{
    staticObjList.insert(std::pair<int,StaticObjects*>(KEY,new EndPoints(X,Y,Z)));
}


void TileMap::removeStar(const int IX, const int IY)
{
   starList.erase( starList.find(getTileKey(IX,IY)) );
   map[IY][IX] = T_Transparent;
}



