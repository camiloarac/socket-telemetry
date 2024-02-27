#pragma once

#include "point.hpp"

#include <cstdlib>
#include <ctime>
#include <vector>

class PointManager {
public:
  explicit PointManager(unsigned int n, int telemetry_port, int server_port);

  PointManager() = delete;

  void publishTelemetry();

  void startServer();

private:
  std::vector<Point> point_vector_;

  int telemetry_port_;
  int server_port_;
};
