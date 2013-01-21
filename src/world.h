/*
    world.h
    
    defintion for the world class. this will store the data about the
    world in which to simulate within
*/

#ifndef WORLD_H
#define WORLD_H

#include <opencv2/core/core.hpp>

namespace cw {

class World
{
public:
    World();
    ~World() {};
    
    void add_obstacle(int x1, int y1, int x2, int y2);
    
    int width();
    int height();

    const cv::Mat environment();
    const cv::Mat sensor();

private:
    int _width;
    int _height;
    cv::Mat _world;
    cv::Mat _sensor;
}; // class World

} // namespace cw

#endif
