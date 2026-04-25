cmake_minimum_required(VERSION 3.16)
project(MatchingEngine_Proj LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MatchingEngineDriver_v1
    MatchingEngineDriver_v3.cpp
)

target_include_directories(MatchingEngineDriver_v3 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)