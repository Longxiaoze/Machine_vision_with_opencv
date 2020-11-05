cmake_minimum_required(VERSION 3.17)
project(opencv13)


set(CMAKE_CXX_STANDARD 14)


#find_library(OpenCV)
find_package(OpenCV)
include_directories( ${OpenCV_INCLUDE_DIRS} )


add_executable(opencv13 main.cpp)


target_link_libraries(opencv13 ${OpenCV_LIBS})