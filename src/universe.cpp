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
    cv::Mat im = _w.getBackground().clone();
    // draw agents
    for (int ai=0; ai<_na; ai++) {
        cv::circle(im, _agents[ai].centre(), _agents[ai].radius(), 
            _agents[ai].colour(), -1, -8);
    }
    // display result
    cv::imshow("theworld", im);
    cv::waitKey(250);
   
}

void
cw::Universe::animate()
{
    
    cv::RNG rng(0x10);
    unsigned int N = _agents.size();

    display();
    for (int it=0; it<100; it++) {

        // move the agents
        // create shuffled list
        std::vector<unsigned int> order;
        for (unsigned int oi=0; oi<N; oi++) {
            order.push_back(oi);
        }
        for (unsigned int oi=0; oi<N; oi++) {
            // swap 2 indexes around
            unsigned int i = rng.uniform(0,N-1), j = rng.uniform(0,N-1);
            unsigned int temp = order[i];
            order[i] = order[j];
            order[j] = temp;
        }
        move_agents(rng, order, N);
        display();
    } // for it
    
    
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

bool
cw::Universe::collide(unsigned int N, unsigned int ai, cv::Point oxy, cv::Point nxy)
{
    // move agent
    _agents[ai].setCentre(nxy);
    // check there is no intersection after the move
    bool overlap = true;
    for (unsigned int ii=0; ii<N; ii++) {
        if (ii!=ai) { // do not check if this is the agent
            if (intersect(_agents[ai], _agents[ii])) {
                overlap = false;
                break;
            }
        }
    }
    // reset agent location
    _agents[ai].setCentre(oxy);
    
    return overlap;
}

void 
cw::Universe::move_agents(cv::RNG &rng, std::vector<unsigned int> order, unsigned int N)
{
    for (unsigned int oi=0; oi<N; oi++) {
        unsigned int ai = order[oi];
        cv::Point xy = _agents[ai].centre();
        // create candidate moves
        std::vector<cv::Point> p(5, xy);
        p[0].y -= 25;
        p[1].y -= 25; p[1].x -= 25;
        p[2].y -= 25; p[2].x += 25;
        p[3].x -= 25;
        p[4].x += 25;
        
        for (int pi=0; pi<5; pi++)
            std::cout << p[pi] << " ";
        std::cout << std::endl;
        
        // validate the new location
        std::vector<bool> valid(5, true);
        for (unsigned int pi=0; pi<p.size(); pi++) {
            if (collide(oi, ai, xy, p[pi]))
                valid[pi] = false;
        }
        for (int pi=0; pi<5; pi++)
            std::cout << valid[pi] << " ";
        std::cout << std::endl;
        // choose new location from list random
        int pos=-1;
        for (unsigned int pi=0; pi<p.size(); pi++)
            if (valid[pi]) {
                pos = pi;
                break;
            }
        if (pos>=0)
            xy = p[pos];
    
        if (xy.y<0)
            xy.y = _w.height();
        _agents[ai].setCentre(xy);
        p.clear();
        valid.clear();
    }
    
}
