cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(GLEW)
set (GLEW_DIR ${CMAKE_SOURCE_DIR})

find_package (OpenGL REQUIRED)

set (GLEW_LIBRARIES ${OPENGL_LIBRARIES})
add_definitions (-DGLEW_NO_GLU)

include_directories (${GLEW_DIR})
set (GLEW_PUBLIC_HEADERS_FILES ${GLEW_DIR}/GL/wglew.h ${GLEW_DIR}/GL/glew.h ${GLEW_DIR}/GL/glxew.h)
set (GLEW_SRC_FILES ${GLEW_DIR}/glew.c)

add_library (glew SHARED ${GLEW_PUBLIC_HEADERS_FILES} ${GLEW_SRC_FILES})
set_target_properties (glew PROPERTIES COMPILE_DEFINITIONS "GLEW_BUILD")               
add_library (glew_s STATIC ${GLEW_PUBLIC_HEADERS_FILES} ${GLEW_SRC_FILES})
set_target_properties (glew_s PROPERTIES COMPILE_DEFINITIONS "GLEW_STATIC")

if (MSVC)
  # add options from visual studio project
  target_compile_definitions (glew PRIVATE "GLEW_BUILD")
  target_compile_definitions (glew_s PRIVATE "GLEW_STATIC")
endif ()

target_link_libraries (glew LINK_PUBLIC ${GLEW_LIBRARIES})
target_link_libraries (glew_s ${GLEW_LIBRARIES})

set(GLEWINFO_SRC_FILES ${GLEW_DIR}/glewinfo.c)
add_executable (glewinfo ${GLEWINFO_SRC_FILES})
target_link_libraries (glewinfo glew)

set (VISUALINFO_SRC_FILES ${GLEW_DIR}/visualinfo.c)
add_executable (visualinfo ${VISUALINFO_SRC_FILES})
target_link_libraries (visualinfo glew)
  
TopAddTarget(glew)
TopAddTarget(glew_s)
TopAddTarget(glewinfo)
TopAddTarget(visualinfo)
ConfigureAll()