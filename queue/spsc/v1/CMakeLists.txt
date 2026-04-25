cmake_minimum_required(VERSION 3.16)
project(SPSC_RingBuffer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SpScRingBufferConsumer_v1
    SpScRingBufferConsumer_v1.cpp
)

target_include_directories(SpScRingBufferConsumer_v1 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)