#include "point.hpp"


Point::Point(int x, int y)
    : target_x_(x), 
    target_y_(y), 
    curr_x_(target_x_), 
    curr_y_(target_y_), 
    update_time_(std::chrono::high_resolution_clock::now()) 
    {}

std::pair<int, int> Point::getCurrentPose() const {
    return std::make_pair(curr_x_, curr_y_); // auto [curr_x, curr_y] = myPoint.getCurrentPose();
}

void Point::setTargetPose(int target_x, int target_y) {
    target_x_ = target_x;
    target_y_ = target_y;
}