#include "point.hpp"


Point::Point(int x, int y)
    : target_x_(x), 
    target_y_(y), 
    curr_x_(target_x_), 
    curr_y_(target_y_), 
    update_time_x_(std::chrono::high_resolution_clock::now()),
    update_time_y_(update_time_x_),
    delta_pos_normalized_x_(0),
    delta_pos_normalized_y_(0)
    {}

std::pair<int, int> Point::getCurrentPose() const {
    return std::make_pair(curr_x_, curr_y_);
}

void Point::setTargetPose(int target_x, int target_y) {
    target_x_ = target_x;
    target_y_ = target_y;
    float delta_x = static_cast<float>(target_x_ - curr_x_);
    float delta_y = static_cast<float>(target_y_ - curr_y_);
    float norm = std::hypot(delta_x, delta_y);
    delta_pos_normalized_x_ = delta_x/norm;
    delta_pos_normalized_y_ = delta_y/norm;
    update_time_x_ = std::chrono::high_resolution_clock::now();
    update_time_y_ = update_time_x_;
}

void Point::updatePose() {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration_x =  now - update_time_x_;
    std::chrono::duration<float> duration_y =  now - update_time_y_;
    int delta_pos_x = static_cast<int>(delta_pos_normalized_x_ * duration_x.count() * velocity_);
    int delta_pos_y = static_cast<int>(delta_pos_normalized_y_ * duration_y.count() * velocity_);
    if (std::abs(delta_pos_x) > 0 && curr_x_ != target_x_) {
        curr_x_ += delta_pos_x;
        update_time_x_ = std::chrono::high_resolution_clock::now();
    }
    if (std::abs(delta_pos_y) > 0 && curr_y_ != target_y_) {
        curr_y_ += delta_pos_y;
        update_time_y_ = std::chrono::high_resolution_clock::now();
    }
}