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
    Universe(const int na);
    
    const int nagents();
    void animate(const int N, bool display=false);
    void draw(bool display);

    //void draw();
    //void update();
    
private:
    int _na;
    World _world;
    std::vector<Agent> _agents; 
    //int _width, _height;
    //std::vector<cv::Scalar> _agents; // (x,y,v_x,v_y
    //std::vector<cv::Scalar> _acolour; // (r,g,b,a) of agents
    //std::vector<unsigned int> _aradius; // size of agent
    //std::vector<int> _order;
    cv::RNG _rng;
    
    void initialise();
    //void initial_location(bool reset=false, int ai=-1);
    //bool overlap(int x, int y, float r, unsigned int ai);

}; // class Universe

} // namespace cw

#endif // UNIVERSE_HH
