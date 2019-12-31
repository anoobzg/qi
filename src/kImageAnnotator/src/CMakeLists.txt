cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(kImageAnnotator LANGUAGES CXX VERSION 0.2.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(QT_MIN_VERSION "5.6.1")
find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets Test)

#set(KCOLORPICKER_MIN_VERSION "0.1.0")
#find_package(kColorPicker ${KCOLORPICKER_MIN_VERSION} REQUIRED)

set(BASEPATH "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${BASEPATH}")
include_directories("${BIN_OUTPUT_DIR}/../src/kColorPicker/src/include/")

add_subdirectory(src)
add_subdirectory(example)

add_library(kImageAnnotator
			${KIMAGEANNOTATOR_SRCS}
			${CMAKE_CURRENT_SOURCE_DIR}/include/kImageAnnotator/KImageAnnotator.h
			${CMAKE_CURRENT_SOURCE_DIR}/icons/kImageAnnotator_icons.qrc
			)

add_library(kImageAnnotator::kImageAnnotator ALIAS kImageAnnotator)

target_include_directories(kImageAnnotator
						   PUBLIC
						   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
						   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
						   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
						   )

if (UNIX)
	target_link_libraries(kImageAnnotator PUBLIC Qt5::Widgets X11)
else ()
	target_link_libraries(kImageAnnotator PUBLIC Qt5::Widgets
						debug "${LIB_OUTPUT_DIR}/Debug/kColorPicker.lib" optimized "${LIB_OUTPUT_DIR}/Release/kColorPicker.lib")
endif ()

#qi_lib(kImageAnnotator kColorPicker)

target_compile_definitions(kImageAnnotator PRIVATE KIMAGEANNOTATOR_LIB)

TopAddTarget(kImageAnnotator)
ConfigureAll()
