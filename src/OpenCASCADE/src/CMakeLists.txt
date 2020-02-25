cmake_minimum_required ( VERSION 2.6)

#if (NOT BUILD_TYPE)
  #set(BUILD_TYPE "Release" CACHE STRING "Build type of the OCCT" FORCE)
  #SET_PROPERTY(CACHE BUILD_TYPE PROPERTY STRINGS Release Debug)
#endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

#set(CMAKE_CONFIGURATION_TYPES ${BUILD_TYPE} CACHE INTERNAL "" FORCE)

project(OCCT)

add_subdirectory(adm/cmake)

ConfigureAll()