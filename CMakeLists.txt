cmake_minimum_required(VERSION 3.10.0)
project(RawExpr VERSION 0.1.0 LANGUAGES CXX)

find_package(fmt CONFIG REQUIRED)

add_executable(RawExpr src/main.cpp)

target_include_directories(RawExpr PRIVATE include)

target_link_libraries(RawExpr PRIVATE fmt::fmt)