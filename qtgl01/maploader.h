#ifndef MAPLOADER_H
#define MAPLOADER_H

#include<vector>

class MapLoader
{
private:
    std::vector< std::vector<char> > map;
    unsigned int width;
    unsigned int height;
public:
    MapLoader();
    inline
    unsigned int getMapWidth(){return width;}
    inline
    unsigned int getMapHeight(){return height;}

    void loadMap(const char* path);
    void printMap();
};

#endif // MAPLOADER_H
