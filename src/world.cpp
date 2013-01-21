/*
    world.cpp
    
    implementation of the world class
*/

#include "world.h"

cw::World::World()
    : _width(500), _height(500), 
    _world(_height, _width, CV_8UC3, cv::Scalar(255,255,255)),
    _sensor(_height, _width, CV_8UC1, cv::Scalar(0))
{

}

void 
cw::World::add_obstacle(int x1, int y1, int x2, int y2)
{
    // draw a rectangle on the environment
    cv::rectangle(_world, cv::Point(x1,y1), cv::Point(x2,y2), 
        cv::Scalar(0,0,0,0), -1);
    // draw on the sensor data as well
    cv::rectangle(_sensor, cv::Point(x1,y1), cv::Point(x2,y2), 
        cv::Scalar(1), -1);
    
    
}

int
cw::World::width()
{
    return _width;
}

int
cw::World::height()
{
    return _height;
}

const cv::Mat
cw::World::environment()
{
    return _world;
}

const cv::Mat
cw::World::sensor()
{
    return _sensor;
}
