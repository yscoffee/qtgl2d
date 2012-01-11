#ifndef TEST_PLAYER_H
#define TEST_PLAYER_H
#include <gtest/gtest.h>
#include "players.h"
#include "movingobjects.h"

namespace {

class testplayer: public testing::Test
{
protected:
    testplayer(){}
    virtual ~testplayer() {}
    virtual void SetUp() {}

    void doSomeHelp(){}

    Players p;
};

// A demo of call TEST FUNCTION
TEST_F(testplayer, Test_VXVY)
{
    p.resetState();
    EXPECT_EQ(p.getVY(),0);
    EXPECT_EQ(p.getVX(),0);
    p.performFalling(10);
    EXPECT_LT(p.getVY(),0);
    p.collideHorizontal();
    EXPECT_EQ(p.getVX(),0);
    p.collideVertical();
    EXPECT_EQ(p.getVY(),0);
}
TEST_F(testplayer, Test_scores)
{
    EXPECT_EQ(p.scores,0);
}
TEST_F(testplayer, Test_XY)
{
    p.resetState();
    EXPECT_EQ(p.getX(),50);
    EXPECT_EQ(p.getY(),50);
}
TEST_F(testplayer,Test_H_W)
{
    EXPECT_GT(p.getWidth(),0);
    EXPECT_GT(p.getHeight(),0);
    EXPECT_EQ(p.getWidth(),2*p.getHalfWidth());
    EXPECT_EQ(p.getHeight(),2*p.getHalfHeight());
}
TEST_F(testplayer,Test_HALF_H_W)
{
    EXPECT_GT(p.getHalfWidth(),0);
    EXPECT_GT(p.getHalfHeight(),0);
}
}//namespace

#endif // TEST_PLAYER_H
