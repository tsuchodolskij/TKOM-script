cmake_minimum_required(VERSION 3.13)
project(TKOM-script)

set(CMAKE_CXX_STANDARD 14)

add_executable(TKOM main.cpp scanner.cpp scanner.h source.cpp source.h token.cpp token.h token_type.h)