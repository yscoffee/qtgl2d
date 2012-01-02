#ifndef TESTFLOOR_H
#define TESTFLOOR_H
#include <gtest/gtest.h>
#include "floors.h"

namespace {

class testfloor: public testing::Test
{
protected:
    testfloor(){}
    virtual ~testfloor() {}
    virtual void SetUp() {}

    void doSomeHelp(){}

    Floors f;
};


TEST_F(testfloor,Test_H_W)
{
    EXPECT_GT(f.getWidth(),0);
    EXPECT_GT(f.getHeight(),0);
}

}

#endif // TESTFLOOR_H
