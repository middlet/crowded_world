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
    
    int width();
    int height();


private:
    int _width;
    int _height;
    cv::Mat _world;
}; // class World

} // namespace cw

#endif
