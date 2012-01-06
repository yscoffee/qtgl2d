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
    int width;
    int height;

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
    int getConvertAndAlignedCoord(const int C, const int L=TileMap::TILE_SIZE ){
        return static_cast<int>((C-1)*TILE_SIZE + TILE_SIZE/2);
    }

    inline
    int map2World_X(const int X, const int L=TileMap::TILE_SIZE  ){
        return static_cast<int>( X*L + L/2);
    }
    inline
    int map2World_Y(const int Y, const int L=TileMap::TILE_SIZE  ){
     //   return static_cast<int>((height-Y-1)*L + L/2);
        return static_cast<int>( Y*L + L/2);
    }

    inline
    unsigned int world2Map_X(const int X, const int L=TileMap::TILE_SIZE  ){
        return static_cast<unsigned int>(floor(static_cast<float>((X-L/2)/L)));
    }

    inline
    unsigned int world2Map_Y(const int Y, const int L=TileMap::TILE_SIZE  ){
        //return height-1-(static_cast<unsigned int>(floor((Y-L/2)/L*1.0)));
        return static_cast<unsigned int>(floor(static_cast<float>((Y-L/2)/L)));

    }



    inline
    unsigned int getMapScriptWidth(){return width;}

    inline
    unsigned int getMapScriptHeight(){return height;}

    bool isCollided(const int,const int,const int,const int);
    bool hasAObjInMap(const int x,const int y);
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

    void tileCollisionCheck(Players &);
    bool starsCollisionCheck(const int X, const int Y, const int W, const int H);
    void printTileMap();
    void printObjLists();
};

#endif // MAPLOADER_H
