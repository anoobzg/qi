macro(IncludeLibmad)
include_directories("${CMAKE_SOURCE_DIR}/../../Libmad/src/")
include_directories("${CMAKE_BINARY_DIR}/../../Libmad/build/")
endmacro()

macro(LinkStaticLibmad target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/libmad-static.lib" optimized "${LIB_RELEASE_PATH}/libmad-static.lib")
endmacro()