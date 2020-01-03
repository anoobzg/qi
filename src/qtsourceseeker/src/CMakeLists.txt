cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(QTSourceSeeker)

set(QT_MIN_VERSION "5.6.1")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets Gui)

macro(add_seek_project source)
set(SOURCE_SEEKER_PROJECT "source_seeker_${source}")
add_executable(${SOURCE_SEEKER_PROJECT} "${source}.cpp")
target_link_libraries(${SOURCE_SEEKER_PROJECT} PUBLIC Qt5::Widgets)
TopAddTarget(${SOURCE_SEEKER_PROJECT})
endmacro()

add_seek_project(widget)
ConfigureAll()