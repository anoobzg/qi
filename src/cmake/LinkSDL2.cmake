macro(IncludeSDL2)
include_directories("${CMAKE_SOURCE_DIR}/../../SDL2/src/include/")
include_directories("${CMAKE_BINARY_DIR}/../../SDL2/build/")
endmacro()

macro(LinkSDL2 target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/SDL2d.lib" optimized "${LIB_RELEASE_PATH}/SDL2.lib")
endmacro()

macro(LinkStaticSDL2 target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/SDL2-staticd.lib" optimized "${LIB_RELEASE_PATH}/SDL2-static.lib")
endmacro()

macro(LinkSDL2Main target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/SDL2maind.lib" optimized "${LIB_RELEASE_PATH}/SDL2main.lib")
endmacro()