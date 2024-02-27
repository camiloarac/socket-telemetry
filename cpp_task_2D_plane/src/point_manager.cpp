#include "point_manager.hpp"

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <mutex>


#define BUFFER_SIZE 2048

using namespace std::chrono_literals;

std::mutex points_mutex;

PointManager::PointManager(unsigned int n, int telemetry_port, int server_port)
      : telemetry_port_(telemetry_port), server_port_(server_port) {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  point_vector_.reserve(n);
  for (auto i = 0; i < n; ++i) {
    point_vector_.emplace_back(std::rand() % 101 - 50,
                                std::rand() % 101 - 50);
  }
}

void PointManager::publishTelemetry() {
  int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

  if (udp_socket == -1) {
    perror("socket() for the telemetry failed");
    exit(1);
  }

  // Set up the server address structure
  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(telemetry_port_);
  server_address.sin_addr.s_addr = INADDR_ANY; // my local IP

  // Infinite loop to send messages
  while (true) {
    std::lock_guard<std::mutex> lock(points_mutex);
    for (auto& elm : point_vector_) {
      elm.updatePose();
      auto pose = elm.getCurrentPose();
      if (sendto(udp_socket, &pose, sizeof(pose), 0,
          (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("sendto() for the telemetry failed");
        exit(1);
      }
    }
    if (program_end_)
        break;
  }
  close(udp_socket);
  std::cout << "The telemetry socket was closed...\n";
}

void PointManager::startServer() {
  int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

  if (udp_socket == -1) {
    perror("socket() for the user interaction server failed");
    exit(1);
  }

  // Set up the server address structure
  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(server_port_);
  server_address.sin_addr.s_addr = INADDR_ANY; // my local IP

  // Bind the socket to the server address
  if (bind(udp_socket, (struct sockaddr *)&server_address,
           sizeof(server_address)) == -1) {
    perror("bind() to the port for user interaction failed");
    exit(1);
  }

  // Buffer to receive messages
  char buffer[BUFFER_SIZE];

  sockaddr their_addr;
  socklen_t addr_len;
  int numbytes;
  int index, x, y;

  // Infinite loop to listen for messages
  while (true) {
    if ((numbytes = recvfrom(udp_socket, buffer, BUFFER_SIZE-1 , 0,
        (struct sockaddr *)&their_addr, &addr_len)) == -1) {
      perror("recvfrom");
      exit(1);
    }
    if (numbytes == 12) {
      index = ((uint8_t)buffer[0] << 24) | ((uint8_t)buffer[1] << 16) | 
              ((uint8_t)buffer[2] << 8)  | ((uint8_t)buffer[3]);
      x = ((uint8_t)buffer[4] << 24) | ((uint8_t)buffer[5] << 16) | 
          ((uint8_t)buffer[6] << 8)  | ((uint8_t)buffer[7]);
      y = ((uint8_t)buffer[8] << 24) | ((uint8_t)buffer[9] << 16) | 
          ((uint8_t)buffer[10] << 8) | ((uint8_t)buffer[11]);
      std::lock_guard<std::mutex> lock(points_mutex);
      point_vector_[index].setTargetPose(x, y);
    }
    if (program_end_)
        break;
  }
  close(udp_socket);
  std::cout << "The server socket for user interaction was closed...\n";
}

void PointManager::setProgramEnd() {
  program_end_ = true;
}

