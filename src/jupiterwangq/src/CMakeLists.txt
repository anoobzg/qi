cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(jupiterwangq)

set(JUPITERWANGQ_MATH_LIB "jupiterwangq_math")
add_subdirectory(math)

include_directories(./math)
set(LIBS ${JUPITERWANGQ_MATH_LIB})
add_executable(jupiterwangq_main main.cpp)
target_link_libraries(jupiterwangq_main "${LIBS}")

TopAddTarget(jupiterwangq_main)

ConfigureAll()
