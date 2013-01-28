/*
    agent_test.cpp
    
    test code for the agent class
*/

#include "../src/agent.h"
#include "../src/world.h"
#include "gtest/gtest.h"

class AgentTest : public ::testing::Test {
protected:
    cw::Agent _a;
    cw::World _w;
}; // class AgentTest

// check the default work constructor is ok
TEST_F(AgentTest, DefaultConstructor_OK) {
    cv::Point xy = _a.motion();
    EXPECT_EQ(xy.x, 0);
    EXPECT_EQ(xy.y, 0);
    EXPECT_EQ(_a.radius(), 10);
}


TEST_F(AgentTest, Move_OK) {
    // always move
    bool result = _a.move(cv::Vec3i(0, 0, 0));
    EXPECT_TRUE(result);
    EXPECT_EQ(_a.motion(), cv::Point(0, -10));
}

TEST_F(AgentTest, Avoid_OK) {
	EXPECT_TRUE(false);
}


TEST_F(AgentTest, ArbitrageOK) {
    
    //_a.arbitrage(_w.sensor());
    EXPECT_TRUE(false);
}

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

