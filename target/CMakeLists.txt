cmake_minimum_required(VERSION 4.0.0)

project(safetyhook-example-target)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
  src/main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
