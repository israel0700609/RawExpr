#include "Evaluator.hpp"
#include "Lexer.hpp"
#include "Logger.hpp"
#include "Parser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  std::ifstream inputFile("expressions.txt");
  if (!inputFile.is_open()) {
    Logger::ERROR("Could not open the file 'expressions.txt' ");
    return 1;
  }
  Lexer lexer(inputFile);

  try {
    std::vector<Token> tokens = lexer.tokenize();

    for (const auto &token : tokens) {
      std::cout << "Type: " << static_cast<int>(token.type) << ", Lexeme: '"
                << token.lexeme << "'"
                << ", Line: " << token.line << ", Column: " << token.column
                << "\n";
    }

    Parser parser(tokens);

    std::unique_ptr<Expr> tree = parser.parse();

    Evaluator evaluator;

    double result = evaluator.evaluate(tree);

    std::cout << "Result: " << result << std::endl;

  } catch (const std::exception &e) {
    Logger::ERROR(e.what());
  }

  return 0;
}