cmake_minimum_required(VERSION 3.17)
project(opencv1)


set(CMAKE_CXX_STANDARD 14)


#find_library(OpenCV)
find_package(OpenCV)
include_directories( ${OpenCV_INCLUDE_DIRS} )


add_executable(opencv1 main.cpp)


target_link_libraries(opencv1 ${OpenCV_LIBS})