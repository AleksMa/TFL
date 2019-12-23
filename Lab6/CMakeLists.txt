cmake_minimum_required(VERSION 3.15)
project(Lab6)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab6 main.cpp Lexer/Lexer.cpp Lexer/Lexer.h Token/Token.cpp Token/Token.h Parser/Parser.cpp Parser/Parser.h)