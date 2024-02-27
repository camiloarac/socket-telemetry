#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

int main() {
  int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

  if (udp_socket == -1) {
    perror("socket() for the telemetry failed");
    exit(1);
  }

  // Set up the server address structure
  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(4444);
  server_address.sin_addr.s_addr = INADDR_ANY; // my local IP

  int point[3] = {0, 15, 9};

  // Send single message
  if (sendto(udp_socket, &point, sizeof(point), 0,
    (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
    perror("sendto() for the initialization failed");
    exit(1);
  }
  close(udp_socket);
  std::cout << "The socket to initialize point was closed...\n";
}