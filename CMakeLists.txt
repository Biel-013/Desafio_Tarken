cmake_minimum_required(VERSION 3.5)
project(OpenCVExample)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIR})

add_executable(OpenCVExample PDI.cpp)

target_link_libraries(OpenCVExample ${OpenCV_LIBS})