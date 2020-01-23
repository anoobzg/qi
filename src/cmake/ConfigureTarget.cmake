set(BIN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/../../../bin")
set(BIN_PLUGINS_OUTPUT_DIR "${CMAKE_BINARY_DIR}/../../../bin/plugins")
set(LIB_OUTPUT_DIR "${CMAKE_BINARY_DIR}/../../../lib")
set(LIB_DEBUG_PATH "${LIB_OUTPUT_DIR}/Debug/")
set(LIB_RELEASE_PATH "${LIB_OUTPUT_DIR}/Release/")
set(ALL_TARGETS)
set(ALL_PLUGIN_TARGETS)
set(ALL_OSG_PLUGIN_TARGETS)

macro(ConfigureTarget TARGET_NAME)
set_target_properties(${TARGET_NAME} PROPERTIES
					LIBRARY_OUTPUT_DIRECTORY_DEBUG "${LIB_OUTPUT_DIR}/Debug/"
					ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${LIB_OUTPUT_DIR}/Debug/"
					RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_OUTPUT_DIR}/Debug/"
					LIBRARY_OUTPUT_DIRECTORY_RELEASE "${LIB_OUTPUT_DIR}/Release/"
					ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${LIB_OUTPUT_DIR}/Release/"
					RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_OUTPUT_DIR}/Release/"
					)
endmacro()
macro(ConfigurePluginTarget TARGET_NAME)
set_target_properties(${TARGET_NAME} PROPERTIES
					LIBRARY_OUTPUT_DIRECTORY_DEBUG "${LIB_OUTPUT_DIR}/Debug/plugins"
					ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${LIB_OUTPUT_DIR}/Debug/plugins"
					RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_OUTPUT_DIR}/Debug/plugins"
					LIBRARY_OUTPUT_DIRECTORY_RELEASE "${LIB_OUTPUT_DIR}/Release/plugins"
					ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${LIB_OUTPUT_DIR}/Release/plugins"
					RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_OUTPUT_DIR}/Release/plugins"
					)
endmacro()
macro(ConfigureOSGPluginTarget TARGET_NAME)
set_target_properties(${TARGET_NAME} PROPERTIES
					LIBRARY_OUTPUT_DIRECTORY_DEBUG "${LIB_OUTPUT_DIR}/Debug/osgPlugins-3.6.5"
					ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${LIB_OUTPUT_DIR}/Debug/osgPlugins-3.6.5"
					RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_OUTPUT_DIR}/Debug/osgPlugins-3.6.5"
					LIBRARY_OUTPUT_DIRECTORY_RELEASE "${LIB_OUTPUT_DIR}/Release/osgPlugins-3.6.5"
					ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${LIB_OUTPUT_DIR}/Release/osgPlugins-3.6.5"
					RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_OUTPUT_DIR}/Release/osgPlugins-3.6.5"
					)
endmacro()

macro(TopAddTarget TARGET_NAME)
list(APPEND ALL_TARGETS ${TARGET_NAME})
endmacro()

macro(AddTarget TARGET_NAME)
#set(INDEX -1)
#list(FIND ALL_TARGETS ${TARGET_NAME} INDEX)
#if(${INDEX} EQUAL -1)
list(APPEND ALL_TARGETS ${TARGET_NAME})
set(ALL_TARGETS ${ALL_TARGETS} CACHE STRING INTERNAL FORCE)
#endif()
endmacro()
macro(AddPluginTarget TARGET_NAME)
#set(INDEX -1)
#list(FIND ALL_TARGETS ${TARGET_NAME} INDEX)
#message(STATUS "${INDEX}++++++++++++++++++++")
#if(${INDEX} EQUAL -1)
list(APPEND ALL_PLUGIN_TARGETS ${TARGET_NAME})
set(ALL_PLUGIN_TARGETS ${ALL_PLUGIN_TARGETS} CACHE STRING INTERNAL FORCE)
#endif()
endmacro()
macro(AddOSGPluginTarget TARGET_NAME)
list(APPEND ALL_OSG_PLUGIN_TARGETS ${TARGET_NAME})
set(ALL_OSG_PLUGIN_TARGETS ${ALL_OSG_PLUGIN_TARGETS} CACHE STRING INTERNAL FORCE)
#endif()
endmacro()

macro(ConfigureAll)
foreach(target ${ALL_TARGETS})
#message(STATUS ${target})
ConfigureTarget(${target})
endforeach()
foreach(target ${ALL_PLUGIN_TARGETS})
#message(STATUS ${target})
ConfigurePluginTarget(${target})
endforeach()
foreach(target ${ALL_OSG_PLUGIN_TARGETS})
#message(STATUS ${target})
ConfigureOSGPluginTarget(${target})
endforeach()
endmacro()

macro(qi_include dir)
include_directories(${BIN_OUTPUT_DIR}/../src/${dir}/src/)
endmacro()
macro(qi_lib target lib)
target_link_libraries(${target} debug "${LIB_OUTPUT_DIR}/Debug/${lib}.lib" optimized "${LIB_OUTPUT_DIR}/Release/${lib}.lib")
endmacro()

# Use the static C library for all build types to a target
# MSVC编译时对指定的target设置'/MT'选项连接static c/c++ library
function (with_mt_if_msvc target)
if(MSVC) 
  # Generator expressions
  get_target_property(_type ${target} TYPE)
  if(_type STREQUAL "STATIC_LIBRARY")
    # 静态库将/MT选项加入INTERFACE_COMPILE_OPTIONS
	target_compile_options(${target} PUBLIC "/MT$<$<STREQUAL:$<CONFIGURATION>,Debug>:d>")
    #target_compile_options( ${target} PUBLIC "${_options}")
  endif()
  #message(STATUS ${_options})
  # Cleanup temporary variables.
  #unset(_mt)
  #unset(_options)
  message(STATUS "target ${target} use static runtime /MT")
endif(MSVC)
endfunction()