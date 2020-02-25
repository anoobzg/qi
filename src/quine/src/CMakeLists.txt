cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(quine)
file(GLOB QUINE_FILES *.cpp) 

foreach(F ${QUINE_FILES})
STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FNAME ${F})
add_executable(${FNAME} ${F})

TopAddTarget(${FNAME})
endforeach()
ConfigureAll()