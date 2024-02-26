#pragma once

#include <utility>

const int POINT_VELOCITY = 1;

// TODO: finish implementation of the class to move point from current pose to
// target pose with velocity POINT_VELOCITY
class Point {
public:
  Point() = delete;

  Point(int x, int y)
      : target_x_(x), target_y_(y), curr_x_(target_x_), curr_y_(target_y_) {}

  std::pair<int, int> getCurrentPose() const {
    // TODO: implmenet function to return curent pose
  }

  void setTargetPose(int target_x, int target_y) {
    target_x_ = target_x;
    target_y_ = target_y;
  }

private:
  int target_x_, target_y_;
  int curr_x_, curr_y_;

  int velocity_{POINT_VELOCITY};
};
