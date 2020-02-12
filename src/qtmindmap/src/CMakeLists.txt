cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(qtmindmap)

set(QT_MIN_VERSION "5.6.1")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets Gui Xml)

include_directories("${CMAKE_SOURCE_DIR}")
include_directories("${CMAKE_BINARY_DIR}")
file(GLOB qtmindmap_UI ui/*.ui)
qt5_wrap_ui(WRAP_FILES ${qtmindmap_UI})

qt5_add_resources(qrc_FILES images/qtmindmap.qrc)

file(GLOB qtmindmap_src include/*.h src/*.cpp)
add_executable(qtmindmap ${qtmindmap_src} ${WRAP_FILES} ${qrc_FILES})
target_link_libraries(qtmindmap Qt5::Core Qt5::Widgets Qt5::Xml)

TopAddTarget(qtmindmap)

ConfigureAll()