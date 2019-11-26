project (DIP)

cmake_minimum_required(VERSION 3.15)
add_subdirectory(src bin)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(imageInterpolation ${OpenCV_LIBS})