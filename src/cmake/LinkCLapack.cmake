macro(IncludeCLapack)
include_directories("${CMAKE_SOURCE_DIR}/../../clapack/src/INCLUDE/")
endmacro()

macro(LinkCLapack target)
target_link_libraries(${target} debug "${LIB_OUTPUT_DIR}/Debug/lapack.lib" optimized "${LIB_OUTPUT_DIR}/Release/lapack.lib")
target_link_libraries(${target} debug "${LIB_OUTPUT_DIR}/Debug/blas.lib" optimized "${LIB_OUTPUT_DIR}/Release/blas.lib")
target_link_libraries(${target} debug "${LIB_OUTPUT_DIR}/Debug/libf2c.lib" optimized "${LIB_OUTPUT_DIR}/Release/libf2c.lib")
endmacro()
