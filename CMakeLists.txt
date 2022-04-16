cmake_minimum_required(VERSION 3.21)
project(NAGYHF)

set(CMAKE_CXX_STANDARD 11)

add_executable(oomm outofmymind.cpp econio.h econio.cpp quest.h quest.cpp fileio.cpp fileio.h)
