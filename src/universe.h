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
    
    void animate();
    void draw();
    void update();
    
private:
    int _na; 
    int _width, _height; 
    std::vector<cv::Scalar> _agents; // (x,y,v_x,v_y
    std::vector<cv::Scalar> _acolour; // (r,g,b,a) of agents
    std::vector<unsigned int> _aradius; // size of agent
    cv::RNG _rng;
    
    void initialise();
    std::vector<unsigned int> nearby_agents(int ai, int radius);


}; // class Universe

} // namespace cw

#endif // UNIVERSE_HH
