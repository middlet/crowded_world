/*
    agent.h

    detail the motion of individual agents
    
*/

#ifndef AGENT_H
#define AGENT_H

#include <opencv2/core/core.hpp>

namespace cw {
    
class Agent {
public:
    Agent();
    Agent(cv::RNG &rng, int width, int height);
    
    void arbitrage();
    
    bool avoid();
    bool move();
    
    const cv::Point centre();
    const cv::Scalar colour();
    const int radius();

    //void setCentre(cv::Point &xy);
    
private:
    int _width;
    int _height;
    cv::Point _xy;
    cv::Scalar _rgb;
    int _r;

    void initialise();

}; // class Agent

} // namespace cw

#endif // AGENT_H
