#include "maploader.h"
#include<fstream>
#include<string>

MapLoader::MapLoader(const unsigned int MW , unsigned int MH):
    MAP_WIDTH(MW),MAP_HIGHT(MH)
{


}

void MapLoader::loadMap(const char *path)
{

    std::fstream fin("path");
    std::string line;
    while(fin.getline(line)){



    }


}
