cmake_minimum_required(VERSION 3.5)

project(mandelbrot_kokkos_cmake LANGUAGES CXX)

# C++11 is for Kokkos
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# default local cmake macro repository
#
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#
# Prevent from build in source tree
# The recommended way of building this app is one build directory per hardware config
# e.g. mkdir build_openmp for openmp build
#  or  mkdir build_cuda for cuda build
#
include(preventBuildInSource)

#
# Init build type: Release, Debug, ...
#
include(initBuildType)

#
# sources
#

# first build kokkos
add_subdirectory(external/kokkos)

add_subdirectory(src)
