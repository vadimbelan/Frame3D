cmake_minimum_required(VERSION 3.10)

project(Frame3D VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(Frame3D src/main.cpp src/video_frame_saver.cpp src/frame_reader.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(Frame3D PRIVATE ${OpenCV_LIBS})
