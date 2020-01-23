project (DIP)

cmake_minimum_required(VERSION 3.15)
add_subdirectory(src bin)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Eigen3 REQUIRED)
include_directories(${Eigen3_INCLUDE_DIRS})

target_link_libraries(imageInterpolation ${OpenCV_LIBS})
target_link_libraries(imageCalculation ${OpenCV_LIBS})
target_link_libraries(crop ${OpenCV_LIBS})
target_link_libraries(histogram ${OpenCV_LIBS})
target_link_libraries(filters ${OpenCV_LIBS})
target_link_libraries(contour ${OpenCV_LIBS})
target_link_libraries(corner ${OpenCV_LIBS})
target_link_libraries(hough_transform ${OpenCV_LIBS})
target_link_libraries(thinning ${OpenCV_LIBS})

target_link_libraries(filters Eigen3::Eigen)