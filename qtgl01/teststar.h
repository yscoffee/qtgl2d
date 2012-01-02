#ifndef TESTSTAR_H
#define TESTSTAR_H

#include <gtest/gtest.h>
#include "stars.h"

namespace {

class teststar: public testing::Test
{
protected:
    teststar(){}
    virtual ~teststar() {}
    virtual void SetUp() {}

    void doSomeHelp(){}

    Floors s;
};


TEST_F(teststar,Test_H_W)
{
    EXPECT_GT(s.getWidth(),0);
    EXPECT_GT(s.getHeight(),0);

}

}


#endif // TESTSTAR_H
