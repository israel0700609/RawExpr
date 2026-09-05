#pragma once

#include <Expressions.hpp>
#include <memory>

class Evaluator {

public:
  double evaluate(std::unique_ptr<Expr> &tree);
};