#include "tilemap.h"
#include "floors.h"
#include "debugtools.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "stars.h"

TileMap::TileMap( ):mapWidth(0),mapHeight(0)
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

    mapHeight=0;
    mapWidth=0;
    //load map script
    //reading map from heighest line to lowest line
    while(getline(fin,line)){


        mapWidth=(mapWidth<line.size())?line.size():mapWidth;
        std::vector<int> newLine;

        //skip a comment line.
        if( line.size() && line[0] =='#' )
            continue;
        else{
        //normal condition
             mapHeight++;
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
    for(int ix=0; ix<map.size();ix++){
        if( map[ix].size() <mapWidth ){
            while( mapWidth - map[ix].size() > 0){
                map[ix].push_back(T_Transparent);
            }
        }
    }

}

void TileMap::printTileMap()
{
    std::cout<<mapWidth<<':'<<mapHeight<<std::endl;

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
                    addFloor( mapCoord2WorldCoord(ix+1), mapCoord2WorldCoord(mapHeight-iy) , Z_VAL );
                    break;
                case T_Enemy:
                    //addEnemy(getConvertAndAlignedCoord(ix),getConvertAndAlignedCoord(height-iy),Z_VAL);
                    break;
                case T_Star:
                    addStar(mapCoord2WorldCoord(ix+1),mapCoord2WorldCoord(mapHeight-iy),Z_VAL);
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
               //<<floorList[ix].getZ()<<' '
               <<" - x:"<<worldCoord2MapCoord(floorList[ix].getX())
               <<" ,y:"<<worldCoord2MapCoord(floorList[ix].getY())
               <<std::endl;
    }
}

//test there is collision or not.
bool TileMap::foundCollision(Players& player)
{
    int x = worldCoord2MapCoord(player.preX);
    int y = worldCoord2MapCoord(player.preY);
    int nextX = worldCoord2MapCoord(player.x);
    int nextY = worldCoord2MapCoord(player.y);

    int dx = nextX-x ;
    int dy = nextY-y ;

    int steps=-1;

    if( abs(dx)>abs(dy) )
        steps=abs(dx);
    else
        steps=abs(dy);

    //not move
    if(steps == 0 )
        return false;

    double deltaX = dx/steps;
    double deltaY = dy/steps;

    bool found=false;
    double px=x;
    double py=y;

    for( int i=0 ; i<steps+1 ;i++){
        px += deltaX ;
        py += deltaY ;

        //test collide
        // map[Y][X]
        if(T_Transparent != map[mapHeight-static_cast<int>(py)-1][static_cast<int>(px)] )
        {
            found=true;
            //align X
            if(dx>0)//right moving
                player.x = mapCoord2WorldCoord(static_cast<int>(px))-TILE_SIZE-player.getHalfWidth();
            else if(dx<0)//left
                player.x = mapCoord2WorldCoord(static_cast<int>(py))+TILE_SIZE+player.getHalfWidth();
            else
                ; //pass

            //align Y
            if(dy>0)// jump
                player.y = mapCoord2WorldCoord(static_cast<int>(px))-TILE_SIZE-player.getHalfHeight();
            else if(dy<0) // falling
                player.y = mapCoord2WorldCoord(static_cast<int>(py))+TILE_SIZE+player.getHalfHeight();
            else
                ;

            break;
        }
    }


    return found;
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

