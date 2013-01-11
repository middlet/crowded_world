/*
    universe.h
    
    the main display class
*/

#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "agent.h"
#include "world.h"


namespace cw {

class Universe
{
public:
    Universe();
    Universe(int na);
    
    void display();
    void animate();


private:
    World _w;
    int _na; 
    std::vector<Agent> _agents;
    
    void create_agents();
    bool intersect(cw::Agent &a1, cw::Agent &a2);
    bool collide(unsigned int N, unsigned int ai, cv::Point oxy, cv::Point nxy);
    void move_agents(cv::RNG &rng, std::vector<unsigned int> order, unsigned int N);

}; // class Universe

} // namespace cw

#endif // UNIVERSE_HH
