# 设置最低的CMake版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(dataStructure)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

# 添加src目录到包含路径
include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(dataStructure)
add_subdirectory(stringOperation)
add_subdirectory(HtmlParser)

