cmake_minimum_required(VERSION 3.10)

project(Frame3D VERSION 1.0 LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем главный файл для сборки
add_executable(Frame3D src/main.cpp)