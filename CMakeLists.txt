cmake_minimum_required(VERSION 3.21)
project(NAGYHF)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Werror -Wall -pedantic -std=c++11 -g -DMEMTRACE")

add_executable(oomm outofmymind.cpp econio.h econio.cpp quest.h quest.cpp game.cpp game.h questqueue.cpp questqueue.h vector.hpp memtrace.cpp memtrace.h tests.cpp tests.h gtest_lite.h)