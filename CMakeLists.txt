cmake_minimum_required(VERSION 3.23)
project(uwb)

set(CMAKE_CXX_STANDARD 14)

add_executable(uwb main.cpp util/UartUtil.cpp util/UartUtil.h util/GpsUtil.cpp util/GpsUtil.h)
