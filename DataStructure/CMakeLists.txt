project(dataStructure)
# 为 module1 创建一个库
aux_source_directory(./src DIR_LIB_SRCS)

add_library(${PROJECT_NAME} DIR_LIB_SRCS)

# 设置 module1 的包含目录，使其他模块可以访问这些目录
target_include_directories(${PROJECT_NAME} PUBLIC inc)