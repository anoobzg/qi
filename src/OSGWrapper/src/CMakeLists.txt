cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)
include(LinkOSG)
include(LinkFreetype)

project(OSGWRAPPER)

include_directories(${CMAKE_SOURCE_DIR}/include/)
IncludeOSG()
IncludeFreetype()

file(GLOB OSGWRAPPER_SRCS ${CMAKE_SOURCE_DIR}/OSGWrapper/*.cpp ${CMAKE_SOURCE_DIR}/OSGWrapper/*.h)
file(GLOB OSGWRAPPER_HEADERS ${CMAKE_SOURCE_DIR}/include/osgWrapper/*.h)

add_definitions("-DOSG_LIBRARY")
add_library(OSGWRAPPER SHARED ${OSGWRAPPER_HEADERS} ${OSGWRAPPER_SRCS})

target_link_libraries(OSGWRAPPER debug "opengl32.lib" optimized "opengl32.lib")
LinkOSG(OSGWRAPPER)
LinkFreetype(OSGWRAPPER)

TopAddTarget(OSGWRAPPER)
ConfigureAll()