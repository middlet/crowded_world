/*
    universe.cpp
    
    implementation of the world class
*/

#include <iostream>

#include "universe.h"


cw::Universe::Universe()
    : _na(1), _world(1), _rng(0x53)
{
#ifdef DEBUG
    std::cerr << __TIME__ " " << __PRETTY_FUNCTION__ << std::endl;
#endif
}

cw::Universe::Universe(const int na)
    : _na(na), _world(na), _rng(0x53)
{
#ifdef DEBUG
    std::cerr << __TIME__ " " << __PRETTY_FUNCTION__ << std::endl;
#endif    
}

const int
cw::Universe::nagents()
{
#ifdef DEBUG
    std::cerr << __TIME__ " " << __PRETTY_FUNCTION__ << std::endl;
#endif
    return _na;
}


void
cw::Universe::animate(const int N, bool display)
{
#ifdef DEBUG
    std::cerr << __TIME__ " " << __PRETTY_FUNCTION__ << std::endl;
#endif
    for (int ni=0; ni<N; ++ni) {
        // update the world
        _world.update();
        // draw the result
        draw(display);
    } // for ni
}

void 
cw::Universe::draw(bool display)
{
#ifdef DEBUG
    std::cerr << __TIME__ " " << __PRETTY_FUNCTION__ << std::endl;
#endif
    if (!display)
        return;
        
    cv::Mat bg = _world.environment();
    for (int ai=0; ai<_na; ++ai) {
        cv::Point xy = _world.location(ai);
        cv::Scalar colour = _world.colour(ai);
        unsigned int r = _world.radius(ai);
        cv::circle(bg, xy, r, colour, -1, -8);
    } // for ai
    cv::imshow("the world", bg);
    
}
