/*
    agent.cpp
    
    implementation of the agent
*/

#include <iostream>

#include "agent.h"

typedef bool (cw::Agent::*FuncPtr)(const cv::Mat);

cw::Agent::Agent()
	: _dxy(cv::Point(0, 0)), _rgb(cv::Scalar(0, 255, 0, 0)), _r(10)
{

}


void
cw::Agent::arbitrage(const cv::Mat sensor)
{
    std::vector<FuncPtr> behaviours;
    behaviours.push_back(&Agent::avoid);
    behaviours.push_back(&Agent::move);
    
    for (unsigned int bi=0; bi<behaviours.size(); bi++) {
        std::cout << (this->*behaviours[bi])(sensor) << std::endl;
    } // for bi
    
}

// move away from obstacles
bool
cw::Agent::avoid(const cv::Mat sensor)
{
    // if obstacle in front
    // then try to move left or right
    
    return false;
}

// just move forward by default
bool
cw::Agent::move(const cv::Mat sensor)
{
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
