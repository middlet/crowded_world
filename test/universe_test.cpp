/*
    universe_test.cpp
    
    test code for the universe class
*/

#include "../src/universe.h"
#include "gtest/gtest.h"

class UniverseTest : public ::testing::Test {
protected:
    cw::Universe _u;
}; // class WorldTest

// check the default work constructor is ok
TEST_F(UniverseTest, DefaultConstructor_OK) {
    EXPECT_EQ(_u.nagents(), 1);
}

// check the constructor is ok
TEST_F(UniverseTest, Constructor_OK) {
    _u = cw::Universe(100);
    EXPECT_EQ(_u.nagents(), 100);
}



int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

