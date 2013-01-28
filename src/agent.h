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
    
    void arbitrage(const cv::Vec3i sensor);
    
    bool avoid(const cv::Vec3i sensor);
    bool move(const cv::Vec3i sensor);
    
    const cv::Point motion();
    const cv::Scalar colour();
    const int radius();

    
private:
    cv::Point _dxy;
    cv::Scalar _rgb;
    int _r;

}; // class Agent

} // namespace cw

#endif // AGENT_H
