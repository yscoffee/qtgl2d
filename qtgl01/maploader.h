#ifndef MAPLOADER_H
#define MAPLOADER_H

class MapLoader
{
public:
    MapLoader(const unsigned int  , unsigned int );
    unsigned int MAP_WIDTH;
    unsigned int MAP_HIGHT;
    void loadMap(const char* path);
};

#endif // MAPLOADER_H
