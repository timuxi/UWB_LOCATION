cmake_minimum_required(VERSION 3.18.4)
project(uwb)
set(CMAKE_CXX_STANDARD 14)

add_executable(uwb main.cpp util/UartUtil.cpp util/UartUtil.h util/GpsUtil.cpp util/GpsUtil.h util/TimeUtil.cpp util/TimeUtil.h)

TARGET_LINK_LIBRARIES(uwb pthread)