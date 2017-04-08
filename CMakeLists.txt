cmake_minimum_required(VERSION 3.7)
project(todo_app)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/server/serve-main.h src/server/serve-main.cpp)
add_executable(todo_app ${SOURCE_FILES})