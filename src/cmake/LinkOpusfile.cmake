macro(IncludeOpusfile)
include_directories("${CMAKE_SOURCE_DIR}/../../opusfile/src/include/")
include_directories("${CMAKE_BINARY_DIR}/../../opusfile/build/")
endmacro()

macro(LinkStaticOpusfile target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/opusfile-static.lib" optimized "${LIB_RELEASE_PATH}/opusfile-static.lib")
endmacro()