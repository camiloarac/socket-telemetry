#include "point_manager.hpp"

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#define BUFFER_SIZE 2048

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
  // https://beej.us/guide/bgnet/html/#client-server-background
  int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

  if (udp_socket == -1) {
    perror("socket() for the telemetry failed");
    exit(1);
  }

  // Set up the server address structure
  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(telemetry_port_);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // Infinite loop to send messages
  while (true) {
    // TODO: implement publishing poses of all points
    // implement mechanism to stop publishing and close socket
  }

  close(udp_socket);
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
  server_address.sin_addr.s_addr = INADDR_ANY;

  // Bind the socket to the server address
  if (bind(udp_socket, (struct sockaddr *)&server_address,
           sizeof(server_address)) == -1) {
    perror("bind() to the port for user interaction failed");
    exit(1);
  }

  // Buffer to receive messages
  char buffer[BUFFER_SIZE];

  // Infinite loop to listen for messages
  while (true) {
    // TODO: implement publishing poses of all points
    // implement mechanism to stop publishing and close socket
  }
  close(udp_socket);
}
