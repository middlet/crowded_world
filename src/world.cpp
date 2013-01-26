/*
    world.cpp
    
    implementation of the world class
*/

#include "world.h"

cw::World::World()
	: _na(1), _width(500), _height(500), 
    _world(_height, _width, CV_8UC3, cv::Scalar(255,255,255)),
    _sensor(_height, _width, CV_8UC1, cv::Scalar(0))
{
	_alocs.push_back(cv::Point(0,0));
}

cw::World::World(int na)
    : _na(na), _width(500), _height(500), 
    _world(_height, _width, CV_8UC3, cv::Scalar(255,255,255)),
    _sensor(_height, _width, CV_8UC1, cv::Scalar(0))
{
	for (int ni=0; ni<_na; ++ni)
		_alocs.push_back(cv::Point(0,0));
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

const int
cw::World::width()
{
    return _width;
}

const int
cw::World::height()
{
    return _height;
}

const int
cw::World::nagents()
{
	return _na;
}

const cv::Point 
cw::World::get_location(int ai)
{
	if (ai<0 || ai>=_na) {
		throw "no such agent";
	}
	
	return _alocs[ai]; 
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
