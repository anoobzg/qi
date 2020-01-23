macro(IncludePNG)
include_directories("${CMAKE_SOURCE_DIR}/../../libpng/src/")
include_directories("${CMAKE_BINARY_DIR}/../../libpng/build/")
endmacro()

macro(LinkPNG target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/libpng17d.lib" optimized "${LIB_RELEASE_PATH}/libpng17.lib")
endmacro()

macro(LinkStaticPNG target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/libpng17_staticd.lib" optimized "${LIB_RELEASE_PATH}/libpng17_static.lib")
endmacro()