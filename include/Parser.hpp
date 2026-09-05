#pragma once
#include <Expressions.hpp>
#include <TokenType.hpp>
class Parser {

private:
  std::vector<Token> tokens;
  size_t current = 0;

  Token peek() const;

  bool isAtEnd() const;

  Token advance();

  bool match(TokenType type);

  Token consume(TokenType type, const std::string &errorMessage);

  std::unique_ptr<Expr> expression();

  std::unique_ptr<Expr> term();

  std::unique_ptr<Expr> factor();

public:
  Parser(std::vector<Token> &tokens);

  std::unique_ptr<Expr> parse();
};