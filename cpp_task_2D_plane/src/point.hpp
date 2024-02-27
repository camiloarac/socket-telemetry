#pragma once

#include <utility>
#include <chrono>
#include <cmath>

const int POINT_VELOCITY = 1;

class Point {
public:
  Point() = delete;

  Point(int x, int y);
  // getter
  std::pair<int, int> getCurrentPose() const;
  // setter
  void setTargetPose(int target_x, int target_y);
  // move point
  void updatePose();

private:
  int target_x_, target_y_;
  int curr_x_, curr_y_;
  std::chrono::time_point<std::chrono::high_resolution_clock> update_time_x_, update_time_y_;
  float delta_pos_normalized_x_, delta_pos_normalized_y_;
  int velocity_{POINT_VELOCITY};
};
