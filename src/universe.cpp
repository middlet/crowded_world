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
cw::Universe::animate(int N)
{
    for (int di=0; di<N; di++)
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
    // shuffle the order of the agents
    for (unsigned int oi=0; oi<(unsigned int)_na/2; oi++) {
        int p1 = _rng.uniform(0,_na-1);
        int p2 = _rng.uniform(0,_na-1);
        int temp = _order[p1];
        _order[p1] = _order[p2];
        _order[p2] = temp;
    }
    for(int ni=0; ni<_na; ni++){
        int x = _agents[ni][0];
        int y = _agents[ni][1];
        int dx = _agents[ni][2];
        int dy = _agents[ni][3];
        unsigned int r = _aradius[ni];
        // if go out of view respawn at origin
        bool respawn = false;
        if (_agents[ni][0]>_width-r || _agents[ni][0]<r)
            respawn = true;
        if (_agents[ni][1]>_height-r || _agents[ni][1]<r) 
            respawn = true;
        // if we collide with another agent dont move this turn
        if (!overlap(x+dx, y+dy, r, ni)) {
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
    // create ordered list for all the agents
    for (unsigned int oi=0; oi<_agents.size(); oi++) {
        _order.push_back(oi);
    }
    
 
    
}

void 
cw::Universe::initial_location(bool reset, int ai)
{
    const float MINR = 6, MAXR = 20;
    
    // random location and size
    bool uniquelocation = false;
    float r;
    int x,y;
    while (!uniquelocation) {
        r = _rng.uniform(MINR, MAXR);
        x = _rng.uniform(10,_width-10);
        if (reset)
            y = _height-r;
        else
            y = _rng.uniform(10, _height-10);
        if (!overlap(x,y,r,ai))
            uniquelocation = true;
    }
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

// do this agent overlap with any other existing ones
bool 
cw::Universe::overlap(int x, int y, float r, unsigned int ai) 
{
    unsigned int N = _agents.size();

    bool overlap = false;
    for (unsigned int ni=0; ni<N; ni++) {
        if (ni!=ai) {
            cv::Scalar aa = _agents[ni];
            int rr = _aradius[ni];
            float d = sqrt( float(x-aa[0])*(x-aa[0]) + float(y-aa[1])*(y-aa[1]));
            if (rr+r>d) {
                overlap = true;
                break;
            }
        }
    }

    return overlap;
}   
