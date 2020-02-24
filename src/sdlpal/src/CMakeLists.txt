cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)
include(LinkSDL2)
include(LinkOggVorbis)
include(LinkOpusfile)
include(LinkLibmad)

project(sdlpal)

include_directories("${CMAKE_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/win32")
IncludeSDL2()
IncludeOggVorbis()
IncludeOpusfile()
IncludeLibmad()

file(GLOB SRC_FILES *.h *.c *.cpp)

set(Win32_SRC "${CMAKE_SOURCE_DIR}/win32/resource.h" 
			  "${CMAKE_SOURCE_DIR}/win32/pal_config.h"
			  "${CMAKE_SOURCE_DIR}/win32/win32.cpp"
			  "${CMAKE_SOURCE_DIR}/win32/sdlpal.rc"
			  )
			  
SOURCE_GROUP(platform_win32 FILES ${Win32_SRC})
			
file(GLOB NATIVE_MIDI_FILES native_midi/*.h native_midi/*.c)			
set(NATIVE_MIDI_SRC "${CMAKE_SOURCE_DIR}/win32/native_midi.cpp" ${NATIVE_MIDI_FILES})
SOURCE_GROUP(native_midi FILES ${NATIVE_MIDI_SRC})

file(GLOB LIB_MAD_FILES libmad/*.h libmad/*.c)
SOURCE_GROUP(libmad FILES ${LIB_MAD_FILES})

file(GLOB ADPLUG_FILES adplug/*.h adplug/*.cpp adplug/*.c)
SOURCE_GROUP(adplug FILES ${ADPLUG_FILES})

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
#add_definitions(-DPAL_HAS_GIT_REVISION)
add_definitions(-DPAL_HAS_PLATFORM_SPECIFIC_UTILS)

add_executable(sdlpal ${SRC_FILES} ${Win32_SRC} ${NATIVE_MIDI_SRC} ${LIB_MAD_FILES} ${ADPLUG_FILES})							 

target_link_libraries(sdlpal opengl32.lib imm32.lib version.lib comctl32.lib winmm.lib)

LinkSDL2(sdlpal)
LinkSDL2Main(sdlpal)
LinkStaticOggVorbis(sdlpal)
LinkStaticOpusfile(sdlpal)

TopAddTarget(sdlpal)
ConfigureAll()