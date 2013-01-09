/*
    universe.cpp
    
    implementation of the world class
*/

#include <iostream>

#include "universe.h"


cw::Universe::Universe()
    : _na(1)
{

    create_agents();

}

cw::Universe::Universe(int na)
    : _na(na)
{
    create_agents();

}


void
cw::Universe::display()
{
    std::cerr << "Universe::display" << std::endl;
    cv::Mat im = _w.getBackground();
    // draw agents
    for (int ai=0; ai<_na; ai++) {
        cv::circle(im, _agents[ai].centre(), _agents[ai].radius(), 
            _agents[ai].colour(), -1, -8);
    }
    // display result
    cv::imshow("theworld", im);
    cv::waitKey();
   
}


void
cw::Universe::create_agents()
{
    cv::RNG rng(0x10);
    for (int ai=0; ai<_na; ai++) {
        int ntries = 0;
        while (ntries<100) {
            Agent a(rng, _w.width(), _w.height());
            // check no overlap with existing agents
            bool oktoadd = true;
            for (unsigned int ai2=0; ai2<_agents.size(); ai2++) {
                if (!intersect(a,_agents[ai2])) {
                    oktoadd = false;
                    break;
                }
            } // for ai2
            if (oktoadd) {
                _agents.push_back(a);
                break;
            }
            else {
                ntries++;
            }
        }
    } // for ai    
    std::cout << "created " << _agents.size() << " agents" << std::endl;
}


bool
cw::Universe::intersect(cw::Agent &a1, cw::Agent &a2)
{
    int r1 = a1.radius(), r2 = a2.radius();
    cv::Point c1 = a1.centre(), c2 = a2.centre();
    // compute euclidean distance
    float d = sqrt( float(c1.x-c2.x)*(c1.x-c2.x) + float(c1.y-c2.y)*(c1.y-c2.y) );
    if (d>(r1+r2))
        return true;
    else
        return false;
}
