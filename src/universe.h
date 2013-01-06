/*
    world.h
    
    defintion for the world class. this will store the data about the
    world in which to simulate within
*/

#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "world.h"


namespace cw {

class Universe
{
public:
    Universe();
    
    void display();

private:
    World _w;
}; // class Universe

} // namespace cw

#endif // UNIVERSE_HH
