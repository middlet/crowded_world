/*
    agent.cpp
    
    implementation of the agent
*/

#include <iostream>

#include "agent.h"

typedef bool (cw::Agent::*FuncPtr)();

cw::Agent::Agent()
    : _width(100), _height(100)
{
    initialise();
}


cw::Agent::Agent(cv::RNG &rng, int width, int height)
    : _width(width), _height(height)
{
}

void
cw::Agent::arbitrage()
{
    std::vector<FuncPtr> behaviours;
    behaviours.push_back(&Agent::avoid);
    behaviours.push_back(&Agent::move);
    
    for (unsigned int bi=0; bi<behaviours.size(); bi++) {
        std::cout << (this->*behaviours[bi])() << std::endl;
        
    } // for bi
    
}

bool
cw::Agent::avoid()
{
    return false;
}

bool
cw::Agent::move()
{
    return true;
}

const cv::Point
cw::Agent::centre()
{
    return _xy;
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

void 
cw::Agent::initialise()
{
    // location
    int x = _width/2;
    int y = _height/2;
    _xy = cv::Point(x, y);
    // colour
    _rgb = cv::Scalar(0, 255 ,0 , 0);
    // radius
    _r = 10;
}

/*

void
cw::Agent::setCentre(cv::Point &xy)
{
    _xy.x = xy.x;
    _xy.y = xy.y;
}
*/
