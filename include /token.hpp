#pragma once 
#include <string>
#include <string_view>
#include <iostream>
#include <variant>
#include "TokenType.hpp"



struct Token{
    TokenType type; 
    std::string_view lexeme;
    std::variant<std::monostate, double, std::string> value;
    int column;
    int line;
};