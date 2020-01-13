macro(IncludeZlib)
include_directories("${CMAKE_SOURCE_DIR}/../../zlib/src/")
include_directories("${CMAKE_BINARY_DIR}/../../zlib/build/")
endmacro()

macro(LinkZlib target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/zlibd.lib" optimized "${LIB_RELEASE_PATH}/zlib.lib")
endmacro()