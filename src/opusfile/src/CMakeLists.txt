cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)
include(LinkOggVorbis)

project(opusfile)

include_directories("${CMAKE_SOURCE_DIR}/include/")
include_directories("${CMAKE_SOURCE_DIR}/celt/")
include_directories("${CMAKE_SOURCE_DIR}/silk/")
include_directories("${CMAKE_SOURCE_DIR}/silk/float/")
include_directories("${CMAKE_SOURCE_DIR}/src/")

IncludeOggVorbis()

file(GLOB SRC_FILES src/*.h src/*.c)
file(GLOB SILK_SRC_FILES silk/*.h silk/*.c)
file(GLOB SILK_FLOAT_SRC_FILES silk/float/*.h silk/float/*.c)
file(GLOB CELT_SRC_FILES celt/*.h celt/*.c)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DHAVE_CONFIG_H)
add_library(opusfile-static STATIC ${SRC_FILES} ${SILK_SRC_FILES} ${CELT_SRC_FILES}
									${SILK_FLOAT_SRC_FILES})							 
LinkStaticOggVorbis(opusfile-static)

TopAddTarget(opusfile-static)
ConfigureAll()