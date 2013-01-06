/*
    world.cpp
    
    implementation of the world class
*/

#include "world.h"

cw::World::World()
    : _width(640), _height(480), _world(_height, _width, CV_8UC3, cv::Scalar(255,255,255))
{

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

cv::Mat
cw::World::getBackground()
{
    return _world;
}
