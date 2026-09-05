#include <Token.hpp>
#include <memory>
#include <stdexcept>
#include <vector>

struct Expr {
  virtual ~Expr() = default;
};

struct NumberExpr : Expr {
  double value;

  NumberExpr(double value) : value(value) {}
};

struct BinaryExpr : Expr {
  std::unique_ptr<Expr> left;
  Token op;
  std::unique_ptr<Expr> right;

  BinaryExpr(std::unique_ptr<Expr> left, std::unique_ptr<Expr> right,
             Token token)
      : left(std::move(left)), right(std::move(right)), op(token) {}
};