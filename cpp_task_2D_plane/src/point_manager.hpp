#pragma once

#include "point.hpp"

#include <cstdlib>
#include <ctime>
#include <vector>

class PointManager {
public:
  explicit PointManager(unsigned int n, int telemetry_port, int server_port)
      : telemetry_port_(telemetry_port), server_port_(server_port) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    point_vector_.reserve(n);
    for (auto i = 0; i < n; ++i) {
      point_vector_.emplace_back(std::rand() % 101 - 50,
                                 std::rand() % 101 - 50);
    }
  }

  PointManager() = delete;

  void publishTelemetry();

  void startServer();

private:
  std::vector<Point> point_vector_;

  int telemetry_port_;
  int server_port_;
};
