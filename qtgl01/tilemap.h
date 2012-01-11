#ifndef TILEMAP
#define TILEMAP

#include<map>
#include "floors.h"
#include "players.h"
#include "stars.h"


class TileMap
{
private:
    enum TileTypes{T_Floor=1, T_Enemy, T_Star, T_Transparent,T_EndOfClass };
    static const int TILE_SIZE=40;
    static const int Z_VAL=1;

    std::vector< std::vector<int> > map;
    int width;
    int height;

    std::map<int,Floors>  floorList;
    std::map<int,Stars>   starList;
    //std::map<int,Objects> enemyList;

    void addFloor(const int,const int,const int,const int);
    void addEnemy(const int,const int,const int,const int);
    void addStar(const int,const int,const int,const int);
    void removeStar(const int,const int);
    void addEndPoint(const int,const int,const int,const int);

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

    inline
    int getTileKey(const int IX,const int IY){
        return IX+getMapScriptHeight()*IY;
    }

    bool isCollided(const int,const int,const int,const int,Players&);
    bool hasAObjInMap(const int x,const int y,Players&);

public:

    TileMap();

    void parseMap(const char*);
    void clear();

    static int tileToPixels(const unsigned int COORD_I );
    bool starsCollisionCheck(const int X, const int Y, const int W, const int H);
    void printTileMap();
    void printObjLists();
    void renderingMap(const int X , const int Y , const int Z,const int SW, const int SH);
    void renderingStars(const int X , const int Y , const int Z,const int SW, const int SH, QGLWidget * p);

    void tileCollisionHandle(Players &);

    //-----------------------------------------------------------------------
    //some getters to retrive basic info.
    inline
    int getTileSize(){return TILE_SIZE;}

    inline
    unsigned int getMapWorldCoordWidth(){return getMapScriptWidth()*TILE_SIZE;}

    inline
    unsigned int getMapWorldCoordHeight(){return getMapScriptHeight()*TILE_SIZE;}
    //-----------------------------------------------------------------------


};

#endif // MAPLOADER_H
