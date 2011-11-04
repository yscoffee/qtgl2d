#include "tilemap.h"
#include "floors.h"
#include "debugtools.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

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
        std::vector<int> newDef;

        //skip a comment line.
        if( line.size() && line[0] =='#' )
            continue;
        else{
        //normal condition
             height++;
            for(int ix=0 ; ix<line.size() ; ix++){
                if( line[ix]!='\n'){
                    switch(line[ix]){
                        case 'E':
                            newDef.push_back(T_Enemy);break;
                        case '*':
                            newDef.push_back(T_Star);break;
                        case '=':
                            newDef.push_back(T_Floor);break;
                        case ' ':
                            newDef.push_back(T_Transparent);break;
                        case '\t' :
                            std::cerr<<"*ERROR Detect \t."<<std::endl;
                        default:
                            std::cerr<<"*Detect undefined block."<<std::endl;
                            throw('err');
                    }
                }
            }
            map.push_back(newDef);
        }
    }


    //normalize
    for(int ix=0; ix<map.size();ix++){
        if( map[ix].size() <width ){
            while( width - map[ix].size() > 0){
                map[ix].push_back(T_Transparent);
            }
        }
    }

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
                    addFloor( getConvertAndAlignedCoord(ix), getConvertAndAlignedCoord(height-iy-1) , Z_VAL );
                    break;
                case T_Enemy:
                  //  addEnemy(getConvertAndAlignedCoord(ix),getConvertAndAlignedCoord(height-iy),Z_VAL);
                    break;
                case T_Star:
                    //addStar(getConvertAndAlignedCoord(ix),getConvertAndAlignedCoord(height-iy),Z_VAL);
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
     floorList.push_back(Floors(X,Y,Z));
}

void TileMap::addEnemy(const int, const int, const int)
{
}

void TileMap::addStar(const int, const int, const int)
{
}

void TileMap::rendering()
{

    for(int ix=0; ix<floorList.size() ; ix++){
        floorList[ix].rendering();
    }
}

void TileMap::printObjLists()
{
    for(int ix=0; ix<floorList.size() ; ix++){
        std::cout<<ix<<':'<<floorList[ix].getX()<<' '
                <<floorList[ix].getY()<<' '
               <<floorList[ix].getZ()<<' '<<std::endl;
    }
}

