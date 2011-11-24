#include<cstdio>
#include <gtest/gtest.h>
#include<iostream> 
//#include "../tilemap.h"
using namespace std;


int testFunction( void ){
	return 1; 
}
 
TEST( MAPLOADER_TEST01 , SimpleInput_1 ) {
  // test case.
  for(int ix=1 ; ix<100000 ; ix++)
	;
    EXPECT_TRUE( testFunction() > 0);

}
TEST( MAPLOADER_TEST02 , SimpleInput_1 ) {
  // test case.
    EXPECT_TRUE( testFunction() > 0);

}
TEST( MAPLOADER_TEST03 , BasicProperties ) {
  // test case.
    EXPECT_TRUE( testFunction() > 0);
    EXPECT_TRUE( testFunction() > 0);
}
TEST( MAPLOADER_TEST04 , SimpleInput_1 ) {


}

int main( int argc , char ** argv ){
  
	cout<<"test the return value of testFunction";
    ::testing::InitGoogleTest(&argc, argv);
	 //m.parseMap("..\\map\\testmap.txt");
     //m.printTileMap();

    return RUN_ALL_TESTS(); 
      
}