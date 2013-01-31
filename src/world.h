/*
    world.h
    
    defintion for the world class. this will store the data about the
    world in which to simulate within
*/

#ifndef WORLD_H
#define WORLD_H

#include <opencv2/core/core.hpp>
#include <exception>
#include <stdexcept>
#include <iostream>
#include "agent.h"

namespace cw {

class World
{
public:
	World();
    World(int na);
    
    void add_obstacle(int x1, int y1, int x2, int y2);
    
    const int width();
    const int height();
    const int nagents();
    
    const cv::Point location(int ai);
    void set_location(int ai, int x1, int y1);
    
    const cv::Scalar colour(int ai);
    const int radius(int ai);

    const cv::Mat environment();
    const cv::Vec3i sensor(int ai);
    
    void update();

private:
	int _na;
    int _width;
    int _height;
    cv::Mat _world;
    cv::Mat _sensor;
    std::vector<Agent> _agents;
    std::vector<cv::Point> _alocs; 
}; // class World

} // namespace cw

#endif
