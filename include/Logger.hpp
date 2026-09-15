#pragma once
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

class Logger {
public:
  static void DEBUG(const std::string &message);
  static void WARNING(const std::string &message);
  static void ERROR(const std::string &message);
  static void PRINT(const std::string &message);

private:
  static void print_timestamp(std::ostream &os);
};