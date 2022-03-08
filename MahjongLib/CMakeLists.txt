cmake_minimum_required(VERSION 3.16)
project(MahjongLib VERSION 1.0)

# target_include_directories(MahjongLib PUBLIC
#     ${PROJECT_SOURCE_DIR}
# )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCES
    ${PROJECT_SOURCE_DIR}/syanten.cpp
    ${PROJECT_SOURCE_DIR}/mjscore.cpp
    ${PROJECT_SOURCE_DIR}/main.cpp
)
add_executable(MahjongLib ${SOURCES})
SET(CMAKE_BUILD_TYPE "Debug")