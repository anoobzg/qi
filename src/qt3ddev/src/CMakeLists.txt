cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(QT3D_DEV)

set(QT_MIN_VERSION "5.6.1")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(QT3D_MODULES Widgets 3DCore 3DRender 3DInput 3DLogic 3DExtras 3DAnimation)
set(QT3D_All Qt5::Widgets Qt5::3DCore Qt5::3DRender Qt5::3DInput Qt5::3DLogic Qt5::3DExtras Qt5::3DAnimation) 

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets Gui ${QT3D_MODULES})

add_subdirectory(simple)
add_subdirectory(basicshapes-cpp)

ConfigureAll()