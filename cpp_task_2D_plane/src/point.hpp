#pragma once

#include <utility>
#include <chrono>

const int POINT_VELOCITY = 1;

// TODO: finish implementation of the class to move point from current pose to
// target pose with velocity POINT_VELOCITY
class Point {
public:
  Point() = delete;

  Point(int x, int y);

  std::pair<int, int> getCurrentPose() const;

  void setTargetPose(int target_x, int target_y);

private:
  int target_x_, target_y_;
  int curr_x_, curr_y_;
  std::chrono::time_point<std::chrono::high_resolution_clock> update_time_;

  int velocity_{POINT_VELOCITY};
};
