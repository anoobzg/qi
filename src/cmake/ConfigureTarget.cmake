set(BIN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/../../../bin")
set(LIB_OUTPUT_DIR "${CMAKE_BINARY_DIR}/../../../lib")
set(ALL_TARGETS)

macro(ConfigureTarget TARGET_NAME)
set_target_properties(${TARGET_NAME} PROPERTIES
					LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR}
					ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR}
					RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR}
					)
endmacro()

macro(TopAddTarget TARGET_NAME)
list(APPEND ALL_TARGETS ${TARGET_NAME})
endmacro()

macro(AddTarget TARGET_NAME)
list(APPEND ALL_TARGETS ${TARGET_NAME})
set(ALL_TARGETS ${ALL_TARGETS} PARENT_SCOPE)
endmacro()

macro(ConfigureAll)
foreach(target ${ALL_TARGETS})
ConfigureTarget(${target})
endforeach()
endmacro()