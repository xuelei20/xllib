cmake_minimum_required(VERSION 2.6)

project(xuel C CXX)
set(CXX_FLAGS
  -g
  -Wall
  -Werror
  -std=c++11
  )

add_subdirectory(comm)
add_subdirectory(demo)
add_subdirectory(test)
