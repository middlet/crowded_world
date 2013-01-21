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
    
    /*
    cv::Point centre();
    cv::Scalar colour();
    int radius();

    void setCentre(cv::Point &xy);
    void arbitrage();
    */
    
private:
    cv::Point _xy;
    cv::Scalar _rgb;
    int _r;

}; // class Agent

} // namespace cw

#endif // AGENT_H
