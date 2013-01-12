/*
    universe.cpp
    
    implementation of the world class
*/

#include <iostream>

#include "universe.h"


cw::Universe::Universe()
    : _na(1), _width(500), _height(500), _rng(0x53)
{
    Universe(_na);
}

cw::Universe::Universe(int na)
    : _na(na), _width(500), _height(500), _rng(0x53)
{
    initialise();
}

void 
cw::Universe::animate()
{
    for (int di=0; di<100; di++)
        draw();
}

void
cw::Universe::draw()
{
    cv::Mat bg(_height, _width, CV_8UC3, cv::Scalar(255,255,255));
    for (int ni=0; ni<_na; ni++) {
        cv::Point xy(_agents[ni][0], _agents[ni][1]);
        cv::Scalar colour = _acolour[ni];
        unsigned int r = _aradius[ni];
        cv::circle(bg, xy, r, colour, -1, -8);
    } // ni
    cv::imshow("the world", bg);
    update();
    cv::waitKey(200);
    
}

void
cw::Universe::update()
{
    for(int ni=0; ni<_na; ni++){
        int dx = _agents[ni][2];
        int dy = _agents[ni][3];
        unsigned int r = _aradius[ni];
        // if go out of view respawn at origin
        bool respawn = false;
        if (_agents[ni][0]>_width-r || _agents[ni][0]<r)
            respawn = true;
        if (_agents[ni][1]>_height-r || _agents[ni][1]<r) 
            respawn = true;
        // if hit another object reflect
        //std::vector<unsigned int> nearby = close_agents(ni, 10);
        
        if (respawn) {
            initial_location(true, ni);
        }
        else {
            _agents[ni][0] += dx;
            _agents[ni][1] += dy;
            _agents[ni][2] = dx;
            _agents[ni][3] = dy;
        }
    }
}


void
cw::Universe::initialise()
{
    
    for (int ni=0; ni<_na; ni++) {
        initial_location();
        // colour
        unsigned char colr = _rng.uniform(0,255);
        unsigned char colg = _rng.uniform(0,255);
        unsigned char colb = _rng.uniform(0,255);
        // add to agents
        _acolour.push_back(cv::Scalar(colr, colg, colb, 0));
    } // ni

    
}

void 
cw::Universe::initial_location(bool reset, int ai)
{
    const float MINR = 6, MAXR = 20;
    
    // random size
    float r = _rng.uniform(MINR, MAXR);
    // random location
    int x = _rng.uniform(10,_width-10);
    int y;
    if (reset)
        y = _height-r;
    else
        y = _rng.uniform(10, _height-10);
    // random velocity
    float angle = _rng.uniform(-M_PI+M_PI/4,-M_PI/4);
    float speed = _rng.uniform(float(r)/8.0, 3*float(r)/4.0);
    int vx = speed*cos(angle);
    int vy = speed*sin(angle);
    // add to agents
    if (reset) {
        _agents[ai] = cv::Scalar(x,y,vx,vy);
        _aradius[ai] = r;
    }
    else {
        _agents.push_back(cv::Scalar(x,y,vx,vy));
        _aradius.push_back(r);
    }
    
} 
