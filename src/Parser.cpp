#include <Parser.hpp>

Parser::Parser(std::vector<Token> &tokens) : tokens(tokens) {}

Token Parser::peek() const { return tokens[current]; }

bool Parser::isAtEnd() const { return peek().type == TokenType::END_OF_FILE; }

Token Parser::advance() {

  if (!isAtEnd()) {
    return tokens[current++];
  }

  return tokens[current];
}

bool Parser::match(TokenType type) {
  if (isAtEnd() || peek().type != type)
    return false;

  advance();
  return true;
}

Token Parser::consume(TokenType type, const std::string &errorMessage) {
  if (peek().type == type) {
    return advance();
  }

  throw std::runtime_error(errorMessage + " at line " +
                           std::to_string(peek().line) + ", column " +
                           std::to_string(peek().column));
}

std::unique_ptr<Expr> Parser::parse() {
  std::unique_ptr<Expr> ast = expression();

  if (!isAtEnd()) {
    throw std::runtime_error(
        "Parsing Error: Something went wrong while parsing the tree.");
  }

  return ast;
}
std::unique_ptr<Expr> Parser::expression() {
  std::unique_ptr<Expr> left = term();

  while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
    Token prevToken = tokens[current - 1];

    std::unique_ptr<Expr> right = term();

    left = std::make_unique<BinaryExpr>(std::move(left), std::move(right),
                                        prevToken);
  }

  return left;
}

std::unique_ptr<Expr> Parser::term() {

  std::unique_ptr<Expr> left = factor();

  while (match(TokenType::MULTIPLY) || match(TokenType::DIVISION)) {

    Token prevToken = tokens[current - 1];

    std::unique_ptr<Expr> right = factor();

    left = std::make_unique<BinaryExpr>(std::move(left), std::move(right),
                                        prevToken);
  }

  return left;
}

std::unique_ptr<Expr> Parser::factor() {
  if (match(TokenType::NUMBER)) {
    Token prevToken = tokens[current - 1];

    double value = std::get<double>(prevToken.value);
    return std::make_unique<NumberExpr>(value);
  }

  if (match(TokenType::LEFT_PARENT)) {
    auto expr = expression();

    consume(TokenType::RIGHT_PARENT, "Expected ')' after expression.");

    return expr;
  }

  Token errorToken = peek();
  throw std::runtime_error("Syntax error: Expected number or '(' at line " +
                           std::to_string(errorToken.line) + ", column " +
                           std::to_string(errorToken.column));
}