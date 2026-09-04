#include "Lexer.hpp"
#include <iostream>
#include <sstream>

int main() {

  std::string input = "454.12 + ( 3 * .50 )";
  std::istringstream inputStream(input);

  Lexer lexer(inputStream);

  try {
    std::vector<Token> tokens = lexer.tokenize();

    for (const auto &token : tokens) {
      std::cout << "Type: " << static_cast<int>(token.type) << ", Lexeme: '"
                << token.lexeme << "'"
                << ", Line: " << token.line << ", Column: " << token.column
                << "\n";
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}