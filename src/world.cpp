/*
    world.cpp
    
    implementation of the world class
*/

#include "world.h"

cw::World::World()
	: _na(1), _width(500), _height(500), 
    _world(_height, _width, CV_8UC1, cv::Scalar(0)),
    _sensor(_height, _width, CV_8UC1, cv::Scalar(0))
{
#ifdef DEBUG
    std::cerr << __TIME__ " " << __PRETTY_FUNCTION__ << std::endl;
#endif
    _agents.push_back(Agent());
	_alocs.push_back(cv::Point(0,0));
}

cw::World::World(int na)
    : _na(na), _width(500), _height(500), 
    _world(_height, _width, CV_8UC1, cv::Scalar(0)),
    _sensor(_height, _width, CV_8UC1, cv::Scalar(0))
{
#ifdef DEBUG
    std::cerr << __TIME__ " " << __PRETTY_FUNCTION__ << std::endl;
#endif
	for (int ni=0; ni<_na; ++ni) {
		_alocs.push_back(cv::Point(0,0));
        _agents.push_back(Agent());
    }
}

void 
cw::World::add_obstacle(int x1, int y1, int x2, int y2)
{

    // draw a rectangle on the environment
    cv::rectangle(_world, cv::Point(x1,y1), cv::Point(x2,y2), 
        cv::Scalar(1), -1);    
    
}

const int
cw::World::width()
{

    return _width;
}

const int
cw::World::height()
{

    return _height;
}

const int
cw::World::nagents()
{

	return _agents.size();
}

const cv::Point 
cw::World::location(int ai)
{
	if (ai<0 || ai>=_na) {
		throw std::runtime_error("no such agent");
	}
	
	return _alocs[ai]; 
}

void 
cw::World::set_location(int ai, int x1, int y1)
{
	if (ai<0 || ai>=_na)
		throw std::runtime_error("no such agent");
	
	if (x1<0 || y1<0 || x1>=_width || y1>=_height)
		throw std::runtime_error("location is outside of the world");
	
	_alocs[ai] = cv::Point(x1, y1);
}

const cv::Scalar
cw::World::colour(int ai) {
    if (ai<0 || ai>=_na) {
		throw std::runtime_error("no such agent");
	}
    
    return _agents[ai].colour();
}

const int
cw::World::radius(int ai) {
    if (ai<0 || ai>=_na) {
		throw std::runtime_error("no such agent");
	}
    
    return _agents[ai].radius();
}

const cv::Mat
cw::World::environment()
{
    return _world;
}

const cv::Vec3i
cw::World::sensor(int ai)
{
#ifdef DEBUG
    std::cerr << __TIME__ " " << __PRETTY_FUNCTION__ << std::endl;
#endif
    if (ai<0 || ai>=_na)
		throw std::runtime_error("no such agent");
    
    cv::Point xy = _alocs[ai];
    
    // return the distance to objects in each of 3 directions
    // if no object distance = 0
    int front = 0;
    for (int yi=xy.y; yi>=0; --yi) {
        if (_world.at<uchar>(xy.x,yi)>0) {
            front = xy.y-yi;
            break;
        }
    }
    int left = 0;
    for (int xi=xy.x; xi>=0; --xi) {
        if (_world.at<uchar>(xi,xy.y)>0) {
            left = xy.x-xi;
            break;
        }
    }
    int right = 0;
    for (int xi=xy.x; xi<_width; ++xi) {
        if (_world.at<uchar>(xi,xy.y)>0) {
            right = xi-xy.x;
            break;
        }
    }
    
    
    return cv::Vec3i(front, left, right);
}

void
cw::World::update() {
#ifdef DEBUG
    std::cerr << __TIME__ " " << __PRETTY_FUNCTION__ << std::endl;
#endif
    for (int ai=0; ai<_na; ++ai) {
        cv::Mat cstate = _world.clone();
        // current location
        cv::Point xy = _alocs[ai];
        int r = _agents[ai].radius();
        // add existing agent locations
        for (int ai2=0; ai2<_na; ++ai2) {
            cv::Point xy2 = _alocs[ai2];
            int r2 = _agents[ai2].radius();
            cv::circle(cstate, xy2, r2, cv::Scalar(2), -1, -8);
        }
        // proposed motion
        cv::Point dxy = _agents[ai].motion();
        // check we can move there by checking
        int sx, ex;
        if (dxy.x<0) {
            sx = xy.x+r;
            ex = xy.x+dxy.x-r;
        }
        else {
            sx = xy.x-r;
            ex = xy.x+dxy.x+r;
        }
        bool canmove = true;
        for (int yi=xy.y-r; yi<=xy.y+dxy.y+r; ++yi) {
            for (int xi=sx; xi<=ex; ++xi) {
                if (xi>=0 && xi<_width && yi>=0 && yi<_height) {
                    if (cstate.at<uchar>(xi,yi)>0) {
                        // we cannot do this move
                        canmove = false;
                        break;
                    }
                }
            } // for xi
        } // for yi
        // update the agent location if it could move
        if (canmove) {
            _alocs[ai] = cv::Point(xy.x+dxy.x, xy.y+dxy.y);
        }
    } // for ai
    
}
