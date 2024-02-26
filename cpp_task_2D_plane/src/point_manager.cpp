#include "point_manager.hpp"

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 2048

void PointManager::publishTelemetry() {
  int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

  if (udp_socket == -1) {
    // TODO: implement error handling for socket call
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
    // TODO: implement error handling for socket call
  }

  // Set up the server address structure
  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(server_port_);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // Bind the socket to the server address
  if (bind(udp_socket, (struct sockaddr *)&server_address,
           sizeof(server_address)) == -1) {
    // TODO: implement error handling
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
