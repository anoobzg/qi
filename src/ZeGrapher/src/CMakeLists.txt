cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(ZeGrapher LANGUAGES CXX VERSION 1.6.0)

if (WIN32)
	set(ZG_LANG_INSTAL_DIR "translations")
elseif (APPLE)
	set(ZG_LANG_INSTAL_DIR "../Resources")
elseif (UNIX)
	set(ZG_LANG_INSTAL_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/ksnip/translations")
endif ()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(QT_MIN_VERSION "5.6.1")

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets Network Xml PrintSupport DBus Svg)

if (WIN32)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED WinExtras)
elseif (UNIX AND NOT APPLE)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED X11Extras)

    # Without ECM we're unable to load XCB
    find_package(ECM REQUIRED NO_MODULE)
    set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

    find_package(X11 REQUIRED)
    find_package(XCB COMPONENTS XFIXES)
endif ()

set(BASEPATH "${CMAKE_SOURCE_DIR}")
include_directories("${BASEPATH}")

set(ROOT_SRC main.cpp structures.h information.h information.cpp)
file(GLOB CALCULUS_SRC Calculus/*.h Calculus/*.cpp)
file(GLOB DATAPLOT_SRC DataPlot/*.h DataPlot/*.cpp)
file(GLOB GRAPHDRAW_SRC GraphDraw/*.h GraphDraw/*.cpp)
file(GLOB VALUETABEL_SRC ValuesTable/*.h ValuesTable/*.cpp)
file(GLOB WIDGETS_SRC Widgets/*.h Widgets/*.cpp)
file(GLOB WINDOWS_SRC Windows/*.h Windows/*.cpp)
file(GLOB DATAPLOT_UI DataPlot/*.ui)
file(GLOB WIDGETS_UI Widgets/*.ui)
file(GLOB WINDOWS_UI Windows/*.ui)

message(STATUS ${DATAPLOT_UI})
message(STATUS ${WIDGETS_UI})
message(STATUS ${WINDOWS_UI})

qt5_wrap_ui(WRAP_FILES ${DATAPLOT_UI})
qt5_wrap_ui(WRAP_FILES ${WIDGETS_UI})
qt5_wrap_ui(WRAP_FILES ${WINDOWS_UI})
 
message(STATUS ${WRAP_FILES})
 
add_executable(ZeGrapher ${ROOT_SRC} ${CALCULUS_SRC} ${DATAPLOT_SRC} ${GRAPHDRAW_SRC} ${VALUETABEL_SRC} ${WIDGETS_SRC} ${WINDOWS_SRC} ${WRAP_FILES})
target_link_libraries(ZeGrapher
					  Qt5::Widgets
					  Qt5::Network
					  Qt5::Xml
					  Qt5::PrintSupport
					  Qt5::DBus
					  Qt5::Svg
					  )
					  
TopAddTarget(ZeGrapher)

ConfigureAll()