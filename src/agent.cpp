/*
    agent.cpp
    
    implementation of the agent
*/

#include <iostream>

#include "agent.h"

typedef bool (cw::Agent::*FuncPtr)(const cv::Vec3i);

cw::Agent::Agent()
	: _dxy(cv::Point(0, 0)), _rgb(cv::Scalar(0, 255, 0, 0)), _r(10)
{

}


void
cw::Agent::arbitrage(const cv::Vec3i sensor)
{
    std::vector<FuncPtr> behaviours;
    behaviours.push_back(&Agent::avoid);
    behaviours.push_back(&Agent::move);
    
    for (unsigned int bi=0; bi<behaviours.size(); bi++) {
		bool result = (this->*behaviours[bi])(sensor);
		if (result) // stop if we have a valid behaviour
			break; 
        //std::cout << (this->*behaviours[bi])(sensor) << std::endl;
    } // for bi
    
}

// move away from obstacles
// TODO : split into multiple behaviours???
bool
cw::Agent::avoid(const cv::Vec3i sensor)
{
    // if obstacle in front
    // then try to move left or right
    if (sensor[0]==0) // no obstacle
		return false;
		
	if (sensor[1]==0 || sensor[1]>_r) { // can move left
		_dxy.x = -_r;
		_dxy.y = 0;
		return true;
	}
	
	if (sensor[2]==0 || sensor[2]>_r) { // can move right
		_dxy.x = _r;
		_dxy.y = 0;
		return true;
	}
    
    // if we make it here we cannot move
    _dxy.x = 0;
    _dxy.y = 0;
    return true;
}

// just move forward by default
bool
cw::Agent::move(const cv::Vec3i sensor)
{
    _dxy.x = 0;
    _dxy.y = -_r; 
    return true;
}

const cv::Point
cw::Agent::motion()
{
    return _dxy;
}

const cv::Scalar
cw::Agent::colour()
{
    return _rgb;
}

const int
cw::Agent::radius()
{
    return _r;
}
