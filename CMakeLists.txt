cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(mahjong)
add_executable(mahjong
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        ${PROJECT_SOURCE_DIR}/src/model.cpp
        ${PROJECT_SOURCE_DIR}/src/dataloader.cpp
        ${PROJECT_SOURCE_DIR}/src/core.cpp
        ${PROJECT_SOURCE_DIR}/src/mjenum.cpp
        ${PROJECT_SOURCE_DIR}/src/common.cpp
        ${PROJECT_SOURCE_DIR}/src/syanten_enum.cpp
)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
target_include_directories(mahjong
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(mahjong "${TORCH_LIBRARIES}")
set_property(TARGET mahjong PROPERTY CXX_STANDARD 17)