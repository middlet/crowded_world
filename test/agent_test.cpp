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
    cv::Point xy = _a.centre();
    EXPECT_EQ(xy.x, 50);
    EXPECT_EQ(xy.y, 50);
    EXPECT_EQ(_a.radius(), 10);
}

TEST_F(AgentTest, SetLocation_OK) {
    _a.set_centre(cv::Point(100,100));
    cv::Point xy = _a.centre();
    EXPECT_EQ(xy.x, 100);
    EXPECT_EQ(xy.y, 100);
}

TEST_F(AgentTest, Move_OK) {
    // default move is to just go forward by the radius
    _a.set_centre(cv::Point(100,100));
    int dx, dy;
    bool result = _a.move(&dx, &dy, _w.sensor());
    EXPECT_TRUE(result);
    EXPECT_EQ(dy, -10);
    EXPECT_EQ(dx, 0);  
}

TEST_F(AgentTest, Avoid_OK) {
    // will turn away from the obstacle
    // put agent in front of obstacle
    _w.add_obstacle(100,100,300,300);
    _a.set_centre(cv::Point(200,95));
    int dx, dy;
    bool result = _a.avoid(&dx, &dy, _w.sensor());
    EXPECT_FALSE(result);
    EXPECT_EQ(dx, -10);
    EXPECT_EQ(dy, 0);
    
}


TEST_F(AgentTest, ArbitrageOK) {
    _w.add_obstacle(100,100,300,300);
    _a.arbitrage(_w.sensor());
    EXPECT_TRUE(false);
}

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

