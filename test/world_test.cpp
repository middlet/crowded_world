/*
    world_test.cpp
    
    test code for the world class
*/

#include "../src/world.h"
#include "gtest/gtest.h"

class WorldTest : public ::testing::Test {
protected:
    cw::World _w;
}; // class WorldTest

TEST_F(WorldTest, DefaultConstructor_OK) {
    EXPECT_EQ(480, _w.height());
    EXPECT_EQ(640, _w.width());
}


int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

