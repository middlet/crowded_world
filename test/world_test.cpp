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

// check the default constructor is ok
TEST_F(WorldTest, DefaultConstructor_OK) {
    EXPECT_EQ(500, _w.height());
    EXPECT_EQ(500, _w.width());
    EXPECT_EQ(1, _w.nagents());
}

// check the constructor is ok
TEST_F(WorldTest, Constructor_OK) {
	_w = cw::World(10);
    EXPECT_EQ(500, _w.height());
    EXPECT_EQ(500, _w.width());
    EXPECT_EQ(10, _w.nagents());
}

TEST_F(WorldTest, GetLocation_OK) {
	cv::Point xy = _w.get_location(0);
	EXPECT_EQ(xy.x, 0);
	EXPECT_EQ(xy.y, 0);
	try {
		xy = _w.get_location(-1);
		xy = _w.get_location(1);
		xy = _w.get_location(2);
		ADD_FAILURE() << "should not get here";
	}
	catch (std::runtime_error &e) {
		std::string s = e.what();
		EXPECT_EQ(s, "no such agent");
	}
}

TEST_F(WorldTest, SetLocation_OK) {
	_w.set_location(0, 100, 100);
	cv::Point xy = _w.get_location(0);
	EXPECT_EQ(xy.x, 100);
	EXPECT_EQ(xy.y, 100);
	try {
		_w.set_location(0, -1, 100);
		_w.set_location(-1, 0, 0);
	}
	catch (std::runtime_error &e) {
		std::string s = e.what();
		EXPECT_EQ(s, "location is outside of the world");
	}
}

// check the correct enironment (this is the world plus obstacles)
TEST_F(WorldTest, Environment_OK) {    
    cv::Mat img = _w.environment();
    EXPECT_EQ(img.at<uchar>(0,0), 0);
    EXPECT_EQ(img.at<uchar>(499,499), 0);
}

// check the correct sensor values
TEST_F(WorldTest, Sensor_OK) { 
    _w.add_obstacle(100, 100, 300, 300); 
    // put agent just below the obstacle
    _w.set_location(0, 200, 302);  
    EXPECT_EQ(_w.sensor(0), cv::Vec3i(2, 0, 0));
    // put agent to the right of the object
    _w.set_location(0, 320, 200);
    EXPECT_EQ(_w.sensor(0), cv::Vec3i(0, 20, 0));
    // put agent to the left of the object
    _w.set_location(0, 95, 200);
    EXPECT_EQ(_w.sensor(0), cv::Vec3i(0, 0, 5));
    // put agent nowhere near object
    _w.set_location(0, 50, 50);
    EXPECT_EQ(_w.sensor(0), cv::Vec3i(0, 0, 0));
    
}

// check obstacle in environment 
TEST_F(WorldTest, Obstacle_OK) {
    _w.add_obstacle(100,100,300,300);
    cv::Mat img = _w.environment();
    EXPECT_EQ(img.at<uchar>(100,100), 1);
    EXPECT_EQ(img.at<uchar>(300,300), 1);
    EXPECT_EQ(img.at<uchar>(200,200), 1);
    EXPECT_EQ(img.at<uchar>(99,100), 0);
}

// check update is moving to correct location
TEST_F(WorldTest, Update_SingleAgent) {
    _w.add_obstacle(100,100,300,300);
    // we cant move into obstacle
    _w.set_location(0, 200, 302);
    _w.update();
    EXPECT_EQ(_w.get_location(0), cv::Point(200, 302));
    // no obstacle
}

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

