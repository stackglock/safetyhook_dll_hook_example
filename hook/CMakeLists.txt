cmake_minimum_required(VERSION 4.0.0)

project(safety_example_hook)

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE
  src/main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
