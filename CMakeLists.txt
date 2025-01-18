cmake_minimum_required(VERSION 3.5.0)

project(ethertest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE ETHER_SRC "src/*.cpp")
add_executable(ethertest ${ETHER_SRC})