cmake_minimum_required(VERSION 3.10)

project(ASCIItokiocolor)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} vulkanrender.cc)

target_link_libraries(${PROJECT_NAME} stdc++fs)
