#ifndef TILEMAP
#define TILEMAP

#include<vector>
#include "floors.h"
#include "players.h"
#include "stars.h"
class TileMap
{
private:
    enum TileTypes{T_Floor=1, T_Enemy, T_Star, T_Transparent };
    static const int TILE_SIZE=50;
    static const int Z_VAL=1;

    std::vector< std::vector<int> > map;
    unsigned int width;
    unsigned int height;

    std::vector<Floors> floorList;
    std::vector<Stars> starList;
    std::vector<Objects> enemyList;

    void addFloor(const int,const int,const int);
    void addEnemy(const int,const int,const int);
    void addStar(const int,const int,const int);

    //perform pasering action from tile map to pixel map.
    void setupTileMap();
    //load map script from disk and storege in v<v<char>>map.
    void loadMap(const char* path);

    //convert logical tile coordinate to real coordinate.
    //and align the center point to the specified block.
    inline
    int getConvertAndAlignedCoord(const int C, const unsigned int L=TileMap::TILE_SIZE ){
        return static_cast<int>((C-1)*TILE_SIZE + TILE_SIZE/2);
    }
    inline
    unsigned int getMapScriptWidth(){return width;}

    inline
    unsigned int getMapScriptHeight(){return height;}

public:
    TileMap();

    void parseMap(const char*);
    bool checkFalling(Players&);
    static int tileToPixels(const unsigned int COORD_I );

    void renderingMap(const int X , const int Y , const int Z,const int SW, const int SH);
    void renderingStars(const int X , const int Y , const int Z,const int SW, const int SH, QGLWidget * p);
    //---------------------------------------------------------
    //some getters functions to retrive basic info.
    inline
    int getTileSize(){return TILE_SIZE;}

    inline
    unsigned int getMapWidth(){return getMapScriptWidth()*TILE_SIZE;}

    inline
    unsigned int getMapHeight(){return getMapScriptHeight()*TILE_SIZE;}

    Objects* tileCollisionCheck(const int X,const int Y, const int W ,const int H);
    bool starsCollisionCheck(const int X, const int Y, const int W, const int H);
    void printTileMap();
    void printObjLists();
};

#endif // MAPLOADER_H
