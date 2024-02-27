#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

#define BUFFER_SIZE 2048

int main() {
  int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

  if (udp_socket == -1) {
    perror("socket() for the user interaction server failed");
    exit(1);
  }

  // Set up the server address structure
  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(3333);
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
  int x, y;

  // Loop to listen for messages
  for (size_t i = 0; i < 5000; i++) {
    if ((numbytes = recvfrom(udp_socket, buffer, BUFFER_SIZE-1 , 0,
        (struct sockaddr *)&their_addr, &addr_len)) == -1) {
      perror("recvfrom");
      exit(1);
    }
    x = ((uint8_t)buffer[3] << 24) | ((uint8_t)buffer[2] << 16) | 
        ((uint8_t)buffer[1] << 8)  | ((uint8_t)buffer[0]);
    y = ((uint8_t)buffer[7] << 24) | ((uint8_t)buffer[6] << 16) | 
        ((uint8_t)buffer[5] << 8) | ((uint8_t)buffer[4]);
    std::cout << "x: " << x << ", y: " << y << "\n";
  }
}