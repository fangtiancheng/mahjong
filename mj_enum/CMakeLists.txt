cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(mj_enum)
add_executable(mj_enum
        ${PROJECT_SOURCE_DIR}/mj_enum.cpp
)
target_include_directories(mj_enum
        PUBLIC
        ${PROJECT_SOURCE_DIR}/
)
set_property(TARGET mj_enum PROPERTY CXX_STANDARD 17)