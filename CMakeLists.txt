cmake_minimum_required(VERSION 3.10.0)
project(RawExpr VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt CONFIG REQUIRED)

add_executable(RawExpr
    src/main.cpp
    src/Lexer.cpp
    src/Parser.cpp
    src/Evaluator.cpp
)
target_include_directories(RawExpr PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(RawExpr PRIVATE fmt::fmt)