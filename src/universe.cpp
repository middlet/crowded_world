/*
    universe.cpp
    
    implementation of the world class
*/

#include <iostream>

#include "universe.h"


cw::Universe::Universe()
{

}

void
cw::Universe::display()
{
    std::cerr << "Universe::display" << std::endl;
    cv::imshow("theworld", _w.getBackground());
    cv::waitKey();
   
}
