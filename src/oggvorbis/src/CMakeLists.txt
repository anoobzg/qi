cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(oggvorbis)

include_directories("${CMAKE_SOURCE_DIR}/include/")

file(GLOB SRC_FILES src/*.h src/*.c)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_library(oggvorbis-static STATIC ${SRC_FILES})							 

TopAddTarget(oggvorbis-static)
ConfigureAll()