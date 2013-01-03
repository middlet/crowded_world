/*
    world.h
    
    defintion for the world class. this will store the data about the
    world in which to simulate within
*/

#ifndef WORLD_H
#define WORLD_H

namespace cw {

class World
{
public:
    World() : _width(640), _height(480) {};
    ~World();


private:
    int _width;
    int _height;
}; // class World

} // namespace cw

#endif
