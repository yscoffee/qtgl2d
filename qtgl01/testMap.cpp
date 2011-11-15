#include "tilemap.h"

int testMap(void){


    TileMap m;
    m.parseMap("..\\map\\testmap.txt");
    m.printTileMap();

return 0;
}



