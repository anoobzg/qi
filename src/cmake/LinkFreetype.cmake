macro(IncludeFreetype)
include_directories("${CMAKE_SOURCE_DIR}/../../freetype/src/include/")
include_directories("${CMAKE_BINARY_DIR}/../../freetype/build/include/")
endmacro()

macro(LinkFreetype target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/freetyped.lib" optimized "${LIB_RELEASE_PATH}/freetype.lib")
endmacro()