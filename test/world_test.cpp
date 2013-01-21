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

// check the default work constructor is ok
TEST_F(WorldTest, DefaultConstructor_OK) {
    EXPECT_EQ(500, _w.height());
    EXPECT_EQ(500, _w.width());
}

// check the correct environment
TEST_F(WorldTest, Environment_OK) {    
    cv::Mat img = _w.environment();
    cv::Vec3b e1 = img.at<cv::Vec3b>(0, 0);
    cv::Vec3b e2 = img.at<cv::Vec3b>(499, 499);
    EXPECT_EQ(e1[0], 255);
    EXPECT_EQ(e1[1], 255);
    EXPECT_EQ(e1[2], 255);
    EXPECT_EQ(e2[0], 255);
    EXPECT_EQ(e2[1], 255);
    EXPECT_EQ(e2[2], 255);
}

// check the correct sensor values
TEST_F(WorldTest, Sensor_OK) {    
    cv::Mat snr = _w.sensor();
    EXPECT_EQ(snr.at<uchar>(0,0), 0);
    EXPECT_EQ(snr.at<uchar>(499,499), 0);
}

// check obstacle in environment 
TEST_F(WorldTest, Obstacle_OK) {
    _w.add_obstacle(100,100,300,300);
    // check the world
    cv::Mat img = _w.environment();
    cv::Vec3b e1 = img.at<cv::Vec3b>(100, 100);
    EXPECT_EQ(e1[0], 0);
    EXPECT_EQ(e1[1], 0);
    EXPECT_EQ(e1[2], 0);
    e1 = img.at<cv::Vec3b>(300, 300);
    EXPECT_EQ(e1[0], 0);
    EXPECT_EQ(e1[1], 0);
    EXPECT_EQ(e1[2], 0);
    e1 = img.at<cv::Vec3b>(200, 300);
    EXPECT_EQ(e1[0], 0);
    EXPECT_EQ(e1[1], 0);
    EXPECT_EQ(e1[2], 0);
    // check the sensor
    cv::Mat snr = _w.sensor();
    EXPECT_EQ(snr.at<uchar>(100,100), 1);
    EXPECT_EQ(snr.at<uchar>(300,300), 1);
    EXPECT_EQ(snr.at<uchar>(100,200), 1);
    
    
}

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

