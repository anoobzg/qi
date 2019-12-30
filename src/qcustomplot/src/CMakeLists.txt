cmake_minimum_required(VERSION 2.6)

PROJECT(qcustomplot)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)
include(ImportQT)

set( QCUSTOMPLOT_HEADERS qcustomplot.h )
set( QCUSTOMPLOT_SOURCES qcustomplot.cpp )

set(STATIC_NAME ${PROJECT_NAME}_static)
set(SHARED_NAME ${PROJECT_NAME})
add_library (${SHARED_NAME} SHARED ${QCUSTOMPLOT_HEADERS} ${QCUSTOMPLOT_SOURCES})
set_target_properties (${SHARED_NAME} PROPERTIES COMPILE_DEFINITIONS "QCUSTOMPLOT_COMPILE_LIBRARY")               
add_library(${STATIC_NAME} STATIC ${QCUSTOMPLOT_HEADERS} ${QCUSTOMPLOT_SOURCES} )

qt5_use_modules(${SHARED_NAME} Core Gui Widgets OpenGL PrintSupport)

TopAddTarget(${SHARED_NAME})
TopAddTarget(${STATIC_NAME})
ConfigureAll()
