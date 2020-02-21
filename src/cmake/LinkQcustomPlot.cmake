macro(IncludeQCustomPlot)
include_directories("${CMAKE_SOURCE_DIR}/../../qcustomplot/src/")
endmacro()

macro(LinkQCustomPlot target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/qcustomplot.lib" optimized "${LIB_RELEASE_PATH}/qcustomplot.lib")
endmacro()

macro(LinkStaticQCustomPlot target)
	target_link_libraries(${target} debug "${LIB_DEBUG_PATH}/qcustomplot_static.lib" optimized "${LIB_RELEASE_PATH}/qcustomplot_static.lib")
endmacro()