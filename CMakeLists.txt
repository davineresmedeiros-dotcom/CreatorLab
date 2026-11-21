cmake_minimum_required(VERSION 3.21)

project(CreatorLab VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("$ENV{GEODE_SDK}" STREQUAL "")
    message(FATAL_ERROR "GEODE_SDK is not set. Configure the project with the Geode SDK environment.")
endif()

# Add Geode SDK as a subdirectory so its relative VERSION and cmake/ paths
# resolve from the SDK source folder, not from the CreatorLab project root.
add_subdirectory("$ENV{GEODE_SDK}" "${CMAKE_CURRENT_BINARY_DIR}/geode-sdk")

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
)

setup_geode_mod(${PROJECT_NAME})
