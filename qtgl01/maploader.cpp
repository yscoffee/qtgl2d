#include "maploader.h"
#include<fstream>
#include<string>
#include<vector>
#include<iostream>

MapLoader::MapLoader( )
{


}

//@throw: const string , represent invalid map script;
void MapLoader::loadMap(const char *path)
{
    std::cout<<path<<std::endl;
    std::fstream fin(path);
    if(fin.fail())
         throw('open failed.');

    std::string line;


    //load map script
    //reading map from heighest line to lowest line
    while(getline(fin,line)){

        height++;
        width=(width<line.size())?line.size():width;
        std::vector<char> newDef;

        //skip a comment line.
        if( line.size() && line[0] =='#' )
            continue;
        else{
        //normal

            for(int ix=0 ; ix<line.size() ; ix++){
                if(  line[ix]!='\t' && line[ix]!='\n'){
                    newDef.push_back( line[ix]);
                }
            }
            map.push_back(newDef);
        }
    }


    //normalize
    for(int ix=0; ix<map.size();ix++){
        if( map[ix].size() <width ){
            while(map[ix].size()-width == 0){
                map[ix].push_back(' ');
            }

        }
    }

}

void MapLoader::printMap()
{
    for(int ix=0; ix<map.size();ix++){
        for(int iy=0; iy<map[ix].size();iy++){
            std::cout<<map[ix][iy];
        }
        std::cout<<std::endl;
    }
}
