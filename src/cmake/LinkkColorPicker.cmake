macro(IncludekColorPicker)
include_directories("${CMAKE_SOURCE_DIR}/../../kColorPicker/src/include/")
endmacro()

macro(LinkkColorPicker target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/kColorPicker.lib" optimized "${LIB_RELEASE_PATH}/kColorPicker.lib")
endmacro()