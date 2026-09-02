# Custom Math Expression Parser (C++)

## Overview
This project is a custom-built mathematical expression parser and evaluator written in standard C++ from scratch. It intentionally avoids automated parser generators like **Lex/Yacc (Flex/Bison)** to provide a deep understanding of compiler front-end mechanics, tokenization, and Abstract Syntax Tree (AST) evaluation.

## architecture Pipeline
The system follows a strict, modern compiler-style pipeline with a clean separation of concerns:
`Raw String -> Lexer -> Tokens -> Parser -> Binary AST -> Evaluator -> Result`

## Core Components

### 1. Token & TokenType (Data Structures)
Tokens represent the fundamental syntactic units of the expression.
*   **`TokenType`**: An `enum class` containing `Number`, `Plus`, `Minus`, `Multiply`, `Divide`, `LParen`, `RParen`, and `Eof`.
*   **`Token`**: A `struct` containing:
    *   `type`: The `TokenType`.
    *   `lexeme`: The original string representation (e.g., `"+"`, `"4.5"`).
    *   `value`: A pre-parsed `double` (only populated if the type is `Number`).
~
### 2. Lexer
The `Lexer` is responsible for reading the raw input string, ignoring whitespaces, and breaking the text down into a `std::vector<Token>`.
*   **Efficiency**: Utilizes `std::string_view` to read the input expression without generating unnecessary string copies in memory.

### 3. Parser
The `Parser` receives the vector of tokens and structures them into an Abstract Syntax Tree (AST) while enforcing the correct order of operations (Operator Precedence).
*   **Implementation**: Can be driven by either the **Shunting Yard Algorithm** or **Recursive Descent**.
*   **Parentheses handling**: `(` and `)` tokens are used to dictate the tree's structure during parsing but are **dropped** completely from the final AST.

### 4. ASTNode (The Binary Tree)
The AST is modeled as a pure **Binary Tree** rather than an N-ary tree, as standard arithmetic operators are strictly binary.
*   **Data-Driven, Non-Polymorphic**: To maximize performance and keep memory overhead minimal, the tree avoids OOP inheritance/polymorphism (no virtual tables). Every node is simply an `ASTNode`.
*   **Structure**: 
    ```cpp
    struct ASTNode {
        Token token;
        std::unique_ptr<ASTNode> left;
        std::unique_ptr<ASTNode> right;
    };
    ```
*   **Leaves vs. Internal Nodes**: 
    *   *Leaves* have `left` and `right` as `nullptr` and always contain `Number` tokens.
    *   *Internal Nodes* contain operator tokens and have active `left` and `right` branches.
*   **Memory Safety**: Utilizes `std::unique_ptr` for all branches, ensuring automatic garbage collection when the tree is destroyed.

### 5. Evaluator
The `Evaluator` isolates the calculation logic from the tree structure itself.
*   **Execution**: It performs a **Post-order Traversal (Bottom-Up)** on the binary tree.
*   It recursively reaches the leaf nodes (numbers), pulls their values, and passes them up to their parent operator nodes to compute the final mathematical result at the root.

### 6. Logger / Error Handler
A utility component designated to catch and cleanly report errors.
*   Handles runtime/parsing warnings such as **division by zero**, **unrecognized characters**, or **mismatched parentheses**.