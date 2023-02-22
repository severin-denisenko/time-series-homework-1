cmake_minimum_required(VERSION 3.22)
project(SpectralAnalysis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 20)

file(GLOB GEN_SRC Generator/*)
add_executable(Generator ${GEN_SRC})

file(GLOB SRC Analysis/*)
add_executable(Analysis ${SRC})
