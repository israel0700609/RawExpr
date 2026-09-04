#pragma once
#include "TokenType.hpp"
#include <iostream>
#include <string>
#include <variant>

struct Token {
  TokenType type;
  std::string lexeme;
  std::variant<std::monostate, double, std::string> value;
  int column;
  int line;
};