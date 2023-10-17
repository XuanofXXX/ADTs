# 设置最低的CMake版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(stringOperation)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

# 添加src目录到包含路径
aux_source_directory(${PROJECT_NAME} SRC_LIST)

include_directories(${CMAKE_SOURCE_DIR}/src)

# 将源文件添加到可执行文件
add_executable(lab1_executable lab1.cpp ${CMAKE_SOURCE_DIR}/src/List.cpp ${CMAKE_SOURCE_DIR}/src/LinkedList.cpp)

