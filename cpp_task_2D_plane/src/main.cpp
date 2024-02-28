#include "point_manager.hpp"

// #include <bits/getopt_ext.h>
#include <getopt.h>

#include <iostream>

int main(int argc, char *argv[]) {

  int option;
  int option_index{0};

  unsigned int number_points;
  unsigned int telemetry_port;
  unsigned int server_port;

  if (argc < 4) {
    std::cout << "usage: server -n number_points -t telemetry_port -s server_port\n";
    return(1);
  }

  static struct option long_options[] = {
      {"number_points", required_argument, nullptr, 'n'},
      {"telemetry_port", required_argument, nullptr, 't'},
      {"server_port", required_argument, nullptr, 'p'},
      {nullptr, 0, nullptr, 0} // Required for the end of the options array
  };

  while ((option = getopt_long_only(argc, argv, "", long_options,
                                    &option_index)) != -1) {
    switch (option) {
    case 'p':
      server_port = std::stoi(optarg);
      break;
    case 'n':
      number_points = std::stoi(optarg);
      break;
    case 't':
      telemetry_port = std::stoi(optarg);
      break;
    default:
      std::cout << "Unknown option" << std::endl;
      return 1;
    }
  }

  PointManager manager(number_points, telemetry_port, server_port);

  std::thread t_telemetry(&PointManager::publishTelemetry, &manager);
  std::thread t_server(&PointManager::startServer, &manager);
  char input;
  do {
    std::cout << "Enter 'y' to close the application...\n";
    std::cin >> input;
  } while (input != 'y');
  manager.setProgramEnd();
  t_telemetry.join();
  std::cout << "server listening for a last message to close the application\n";
  t_server.join();
}
