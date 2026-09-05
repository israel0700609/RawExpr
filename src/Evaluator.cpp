#include <Evaluator.hpp>

double Evaluator::evaluate(std::unique_ptr<Expr> &tree) {
  if (!tree) {
    throw std::runtime_error("Evaluation Error: Encountered empty node.");
  }

  if (NumberExpr *numberExpr = dynamic_cast<NumberExpr *>(tree.get())) {
    return numberExpr->value;
  }

  if (BinaryExpr *binaryExpr = dynamic_cast<BinaryExpr *>(tree.get())) {
    double left = evaluate(binaryExpr->left);
    double right = evaluate(binaryExpr->right);

    Token token = binaryExpr->op;
    TokenType tokenType = token.type;

    switch (tokenType) {
    case TokenType::PLUS:
      return left + right;
    case TokenType::MINUS:
      return left - right;
    case TokenType::MULTIPLY:
      return left * right;
    case TokenType::DIVISION:
      if (right == 0) {
        throw std::runtime_error(
            "Evaluation Error: Division by zero at line: " +
            std::to_string(token.line) + ", column " +
            std::to_string(token.column));
      }
      return left / right;
    default:
      throw std::runtime_error(
          "Unknown operator at line: " + std::to_string(token.line) +
          ", column " + std::to_string(token.column));
    }
  }

  throw std::runtime_error("Evaluation Error: Unknown AST node type.");
}