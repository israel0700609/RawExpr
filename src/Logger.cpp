#include "Logger.hpp"

void Logger::DEBUG(const std::string &message) {
  print_timestamp(std::cout);
  std::cout << "Logger | DEBUG message : ";
  PRINT(message);
}

void Logger::WARNING(const std::string &message) {
  print_timestamp(std::cerr);
  std::cerr << "Logger | WARNING message : " << message << "\n";
}

void Logger::ERROR(const std::string &message) {
  print_timestamp(std::cerr);
  std::cerr << "Logger | ERROR message : " << message << "\n";
}

void Logger::PRINT(const std::string &message) { std::cout << message << "\n"; }

void Logger::print_timestamp(std::ostream &os) {
  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);

  os << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %H-%M-%S")
     << "] ";
}