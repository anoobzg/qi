macro(IncludeOggVorbis)
include_directories("${CMAKE_SOURCE_DIR}/../../oggvorbis/src/include/")
include_directories("${CMAKE_BINARY_DIR}/../../oggvorbis/build/")
endmacro()

macro(LinkStaticOggVorbis target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/oggvorbis-static.lib" optimized "${LIB_RELEASE_PATH}/oggvorbis-static.lib")
endmacro()