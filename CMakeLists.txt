cmake_minimum_required(VERSION 3.26)

# CMAKE INCLUDES

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/external/cmake/)
include(CMakePrintHelpers)
include(cmtk/CppLibraryProject)

# CONFIGURATION

disable_in_source_build()
set_build_type_ifndef()

# C++ PROJECT

set_project_name(NAMESPACE "arba" BASE_NAME "math")
string(TIMESTAMP configure_datetime "%Y%m%d-%H%M%S" UTC)
set_project_semantic_version("0.6.0"
    PRE_RELEASE "dev"
    BUILD_METADATA "${configure_datetime}"
)
project(${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    DESCRIPTION "A tiny C++ library providing useful math tools."
    HOMEPAGE_URL "https://github.com/arapelle/arba-math"
    LANGUAGES CXX)
message(STATUS "PROJECT : ${PROJECT_NAME} ${PROJECT_VERSION} ${CMAKE_BUILD_TYPE}")
include(CTest)

# C++ LIBRARY

## Generated/Configured headers:
configure_headers(configured_headers
    FILES
        include/${PROJECT_NAMESPACE}/${PROJECT_BASE_NAME}/version.hpp.in
)

## Headers:
set(headers
    include/arba/math/vec2.hpp
    include/arba/math/concepts.hpp
)

## Add C++ library
add_cpp_library(
    HEADER_ONLY ${PROJECT_NAME}
    HEADERS ${headers} ${configured_headers}
    CXX_STANDARD 20
)

## Link C++ targets:
if(NOT TARGET arba-core)
    find_package(arba-core 0.26.0 REQUIRED CONFIG)
endif()
target_link_libraries(${PROJECT_NAME} INTERFACE arba-core)

## Install C++ library
install_cpp_library(
    HEADER_ONLY ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
)

## Install package
install_library_package(${PROJECT_NAME} INPUT_PACKAGE_CONFIG_FILE cmake/config/package-config.cmake.in)
install_uninstall_script(${PROJECT_NAME} FILENAME uninstall.cmake)

## Add examples:
option_or_set_ifdef(BUILD_${PROJECT_NAME}_EXAMPLES "Build ${PROJECT_NAME} examples or not" OFF BUILD_arba-arba_EXAMPLES)
if(BUILD_${PROJECT_NAME}_EXAMPLES)
    add_subdirectory(example)
endif()

## Add tests:
option_or_set_ifdef(BUILD_${PROJECT_NAME}_TESTS "Build ${PROJECT_NAME} tests or not" OFF BUILD_arba-arba_TESTS)
if(BUILD_${PROJECT_NAME}_TESTS AND BUILD_TESTING)
    add_subdirectory(test)
endif()
