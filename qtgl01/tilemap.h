#ifndef TILEMAP
#define TILEMAP

#include<vector>

class TileMap
{
private:
    std::vector< std::vector<char> > map;
    unsigned int width;
    unsigned int height;
public:
    TileMap();
    inline
    unsigned int getMapWidth(){return width;}
    inline
    unsigned int getMapHeight(){return height;}

    void loadMap(const char* path);
    void printMap();
};

#endif // MAPLOADER_H
