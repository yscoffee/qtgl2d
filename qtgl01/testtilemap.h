#ifndef TESTTILEMAP_H
#define TESTTILEMAP_H
#include "tilemap.h"
#include "players.h"
#include <gtest/gtest.h>

namespace {

class TestTileMap: public testing::Test
{
protected:  // You should make the members protected s.t. they can be
    // accessed from sub-classes.
    TestTileMap(){
        m.parseMap("..\\map\\testmap.txt");

    }
    virtual ~TestTileMap() {

    }
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp() {

    }
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    // virtual void TearDown() {
    // }

    // A helper function that some test uses.
    void doSomeHelp(){}

    // Declares the variables your tests want to use.
    TileMap m;
    Players p;
};

// A demo of call TEST FUNCTION
TEST_F(TestTileMap, MethodPrint) {
    // You can access data in the test fixture here.
    m.printTileMap();
    //direcet call member function
    doSomeHelp();
}
TEST_F(TestTileMap, Properties) {

    //write a test functon
    ASSERT_TRUE(m.getTileSize()>0);
}
TEST_F(TestTileMap,Chekfalling)
{
    //EXPECT_TRUE(m.checkFalling(p));
}
TEST_F(TestTileMap,test_map_H_W)
{
    EXPECT_GT(m.getMapWorldCoordWidth(),0);
    EXPECT_GT(m.getMapWorldCoordHeight(),0);
}

}//namespace

#endif // TESTTILEMAP_H
