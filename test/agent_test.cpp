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
    int rot, trans;
    bool result = _a.move(&trans, &rot);
    EXPECT_TRUE(result);
    EXPECT_EQ(trans, -10);
    EXPECT_EQ(rot, 0);  
}

TEST_F(AgentTest, Avoid_OK) {
    // will turn away from the obstacle
    // put agent in front of obstacle
    _w.add_obstacle(100,100,300,300);
    _a.set_centre(cv::Point(200,95));
    int rot, trans;
    bool result = _a.avoid(&trans, &rot);
    EXPECT_FALSE(result);
    EXPECT_EQ(trans, 10);
    EXPECT_EQ(rot, 1);
    
}


TEST_F(AgentTest, ArbitrageOK) {
    _w.add_obstacle(100,100,300,300);
    _a.arbitrage();
    EXPECT_TRUE(false);
}

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

