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

TEST_F(AgentTest, Avoid_None_OK) {
	// no obstacle so dont avoid
	bool result = _a.avoid(cv::Vec3i(0, 0, 0));
	EXPECT_FALSE(result);
}

TEST_F(AgentTest, Avoid_Front_OK) {
	// obstacle in front so move left
	bool result = _a.avoid(cv::Vec3i(1, 0, 0));
	EXPECT_TRUE(result);
	EXPECT_EQ(_a.motion(), cv::Point(-10, 0));
}

TEST_F(AgentTest, Avoid_FrontLeft_OK) {
	// obstacle front and left so go right
	bool result = _a.avoid(cv::Vec3i(1, 1, 0));
	EXPECT_TRUE(result);
	EXPECT_EQ(_a.motion(), cv::Point(10, 0));
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

