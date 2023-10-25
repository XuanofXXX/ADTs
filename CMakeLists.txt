cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(HTMLPARSER)

add_executable(HTMLPARSER lab2.cpp)

target_link_libraries(HTMLPARSER curl)  # 链接libcurl
