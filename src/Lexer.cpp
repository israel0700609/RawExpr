#include "Lexer.hpp"
#include <cctype>
#include <stdexcept>
#include <string>

Lexer::Lexer(std::istream &inputStream)
    : inputStream(inputStream), line(1), column(0) {

  advance();
}

void Lexer::advance() {

  if (inputStream.get(currentChar)) {
    if (currentChar == '\n') {
      line += 1;
      column = 0;
    } else {
      column += 1;
    }
  } else {
    currentChar = '\0';
  }
}

Token Lexer::scanNumber() {
  std::string lexeme = "";
  int startColumn = column;
  bool hasDot = false;

  while (std::isdigit(currentChar) || currentChar == '.') {
    if (currentChar == '.') {
      if (hasDot) {
        throw std::runtime_error(
            "Lexical Error at line " + std::to_string(line) + ", column " +
            std::to_string(column) + ": Multiple decimal points in number.");
      }
      hasDot = true;
    }

    lexeme += currentChar;
    advance();
  }

  double numericValue = std::stod(lexeme);
  return Token{TokenType::NUMBER, lexeme, numericValue, startColumn, line};
}

void Lexer::skipWhiteSpace() {
  while (currentChar != '\0' && std::isspace(currentChar)) {
    advance();
  }
}

Token Lexer::getNextToken() {
  skipWhiteSpace();

  if (currentChar == '\0') {
    return Token{TokenType::END_OF_FILE, "EOF", std::monostate{}, column, line};
  }

  if (std::isdigit(currentChar)) {
    return scanNumber();
  }

  if (currentChar == '.') {
    char nextChar = inputStream.peek();
    if (nextChar != EOF && std::isdigit(nextChar)) {
      return scanNumber();
    } else {
      throw std::runtime_error("Lexical Error: Unexpected character '.'");
    }
  }

  TokenType type;
  switch (currentChar) {
  case '+':
    type = TokenType::PLUS;
    break;
  case '-':
    type = TokenType::MINUS;
    break;
  case '*':
    type = TokenType::MULTIPLY;
    break;
  case '/':
    type = TokenType::DIVISION;
    break;
  case '(':
    type = TokenType::LEFT_PARENT;
    break;
  case ')':
    type = TokenType::RIGHT_PARENT;
    break;
  default:
    throw std::runtime_error("Lexical Error: Unexpected character at line " +
                             std::to_string(line) + ", column " +
                             std::to_string(column) + " : " + currentChar);
  }
  Token returnToken = {type, std::string(1, currentChar), std::monostate{},
                       column, line};

  advance();

  return returnToken;
}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;
  Token currentToken;

  do {
    currentToken = getNextToken();
    tokens.push_back(currentToken);

  } while (currentToken.type != TokenType::END_OF_FILE);

  return tokens;
}