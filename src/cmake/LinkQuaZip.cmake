macro(IncludeQuaZip)
include_directories("${CMAKE_SOURCE_DIR}/../../quazip/src/")
include_directories("${CMAKE_BINARY_DIR}/../../quazip/build/")
endmacro()

macro(LinkQuaZip target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/quazip5d.lib" optimized "${LIB_RELEASE_PATH}/quazip5.lib")
endmacro()