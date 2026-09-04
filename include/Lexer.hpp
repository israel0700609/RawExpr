#pragma once
#include "Token.hpp"
#include <iostream>
#include <vector>

class Lexer {

public:
  explicit Lexer(std::istream &inputStream);

  Token getNextToken();

  std::vector<Token> tokenize();

private:
  int line;
  int column;
  std::istream &inputStream;
  char currentChar;

  void advance();
  void skipWhiteSpace();
  Token scanNumber();
};