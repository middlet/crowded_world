/*
    agent_test.cpp
    
    test code for the agent class
*/

#include "../src/agent.h"
#include "gtest/gtest.h"

class AgentTest : public ::testing::Test {
protected:
    cw::Agent _a;
}; // class WorldTest

// check the default work constructor is ok
TEST_F(AgentTest, DefaultConstructor_OK) {
    cv::Point xy = _a.centre();
    EXPECT_EQ(xy.x, 50);
    EXPECT_EQ(xy.y, 50);
    EXPECT_EQ(_a.radius(), 10);
}

TEST_F(AgentTest, ArbitrageOK) {
    _a.arbitrage();
    EXPECT_TRUE(false);
}

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

