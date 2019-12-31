cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(kColorPicker LANGUAGES CXX VERSION 0.1.0)

set(QT_MIN_VERSION "5.6.1")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets Test)

add_subdirectory(src)
add_subdirectory(example)

add_library(kColorPicker
			${KCOLORPICKER_SRCS}
			${CMAKE_CURRENT_SOURCE_DIR}/include/kColorPicker/KColorPicker.h
			${CMAKE_CURRENT_SOURCE_DIR}/icons/kColorPicker_icons.qrc
			)

add_library(kColorPicker::kColorPicker ALIAS kColorPicker)

target_include_directories(kColorPicker
						   PUBLIC
						   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
						   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
						   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
						   )

target_link_libraries(kColorPicker PUBLIC Qt5::Widgets)

target_compile_definitions(kColorPicker PRIVATE KIMAGEANNOTATOR_LIB)

TopAddTarget(kColorPicker)
ConfigureAll()