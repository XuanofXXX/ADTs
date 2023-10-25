cmake_minimum_required(VERSION 3.10)

project(HTMLPARSER)

add_executable(HTMLPARSER lab2.cpp)

target_link_libraries(HTMLPARSER curl)  # 链接libcurl
