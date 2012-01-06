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
    static const int TILE_SIZE=30;
    static const int Z_VAL=1;

    std::vector< std::vector<int> > map;
    unsigned int mapWidth;
    unsigned int mapHeight;

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
    int mapCoord2WorldCoord(const int C ){
        return static_cast<int>((C-1)*TILE_SIZE + TILE_SIZE/2 );
    }
    //Convert world coordinate into logic map coordinate
    inline
    int worldCoord2MapCoord(const int C ){
        //return static_cast<int>( (C - TILE_SIZE/2)/TILE_SIZE+1);
        return static_cast<int>(floor(C*1.0/TILE_SIZE)-1);
    }

    inline
    unsigned int getMapScriptWidth(){return mapWidth;}

    inline
    unsigned int getMapScriptHeight(){return mapHeight;}

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

    bool foundCollision(Players& player);
    bool starsCollisionCheck(const int X, const int Y, const int W, const int H);
    void printTileMap();
    void printObjLists();
};

#endif // MAPLOADER_H
