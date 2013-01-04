/*
    world.cpp
    
    implementation of the world class
*/

#include "world.h"

cw::World::World()
    : _width(640), _height(480)
{

}

int
cw::World::width()
{
    return _width;
}

int
cw::World::height()
{
    return _height;
}
