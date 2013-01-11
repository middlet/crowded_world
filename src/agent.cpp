/*
    agent.cpp
    
    implementation of the agent
*/

#include <iostream>

#include "agent.h"


cw::Agent::Agent(cv::RNG &rng, int width, int height)
    : _r(25)
{
    // randomised location
    int x1 = rng.uniform(0, width);
    int y1 = rng.uniform(0, height);
    _xy = cv::Point(x1,y1);
    // randomised colour
    int r = rng.uniform(0, 255);
    int g = rng.uniform(0, 255);
    int b = rng.uniform(0, 255);
    _rgb = cv::Scalar(r, g, b, 0.5);

}

cv::Point
cw::Agent::centre()
{
    return _xy;
}

cv::Scalar
cw::Agent::colour()
{
    return _rgb;
}

int
cw::Agent::radius()
{
    return _r;
}


void
cw::Agent::setCentre(cv::Point &xy)
{
    _xy.x = xy.x;
    _xy.y = xy.y;
}
