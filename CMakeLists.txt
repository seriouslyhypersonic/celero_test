cmake_minimum_required(VERSION 3.13)

project(celero_test)

set(CMAKE_CXX_STANDARD 17)

# ------------------------------------------------------------------------------
# Add Celero as an external project
# ------------------------------------------------------------------------------

find_package(Git REQUIRED)
include(ExternalProject)

message(STATUS "Configuring Celero")
ExternalProject_Add(celero_project
        GIT_REPOSITORY https://github.com/DigitalInBlue/Celero.git
        GIT_TAG master
        GIT_SHALLOW 1
        UPDATE_COMMAND ""
        INSTALL_DIR ${CMAKE_BINARY_DIR}
        CMAKE_ARGS
        -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX:STRING=${CMAKE_BINARY_DIR}
        -DCELERO_COMPILE_DYNAMIC_LIBRARIES:BOOL=OFF
        -DCELERO_ENABLE_EXPERIMENTS:BOOL=OFF
        -DCELERO_ENABLE_FOLDERS:BOOL=OFF)
ExternalProject_Get_Property(celero_project SOURCE_DIR)
ExternalProject_Get_Property(celero_project INSTALL_DIR)
set(CELERO_INSTALL_DIR ${INSTALL_DIR})
message(STATUS "CELERO_INSTALL_DIR=${CELERO_INSTALL_DIR}")

include_directories(${CELERO_INSTALL_DIR}/include)
add_library(libcelero STATIC IMPORTED GLOBAL)
set_property(TARGET libcelero PROPERTY
        IMPORTED_LOCATION_DEBUG
        "${CELERO_INSTALL_DIR}/lib/static/${CMAKE_STATIC_LIBRARY_PREFIX}celerod${CMAKE_STATIC_LIBRARY_SUFFIX}")
set_property(TARGET libcelero PROPERTY
        IMPORTED_LOCATION_RELEASE
        "${CELERO_INSTALL_DIR}/lib/static/${CMAKE_STATIC_LIBRARY_PREFIX}celero${CMAKE_STATIC_LIBRARY_SUFFIX}")
add_dependencies(libcelero celero_project)

# ------------------------------------------------------------------------------

add_executable(benchmark1 benchmark1.cpp)
add_dependencies(benchmark1 libcelero)
target_link_libraries(benchmark1 libcelero)

