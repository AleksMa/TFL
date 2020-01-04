cmake_minimum_required(VERSION 3.15)
project(Lab5)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab5 main.cpp Lexer/Lexer.cpp Lexer/Lexer.h Token/Token.cpp Token/Token.h temp.cpp)