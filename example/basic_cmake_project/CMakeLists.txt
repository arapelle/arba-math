cmake_minimum_required(VERSION 3.18)

project(basic_cmake_project)

add_executable(${PROJECT_NAME} main.cpp)
# Find package math:
find_package(math 0.2.0 CONFIG REQUIRED)
# Use math release shared target:
target_link_libraries(${PROJECT_NAME} PRIVATE arba::math)
# Use math release static target:
#target_link_libraries(${PROJECT_NAME} PRIVATE arba::math-static)

