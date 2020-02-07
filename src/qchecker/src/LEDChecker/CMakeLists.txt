
file(GLOB CHECKER_UI ui/*.ui)
qt5_wrap_ui(WRAP_FILES ${CHECKER_UI})

#source_group(ui FILES "${CHECKER_UI}")

IncludeOpenCV()
include_directories("${CMAKE_BINARY_DIR}/LEDChecker/")
include_directories("${CMAKE_SOURCE_DIR}/LEDAlgrithm/")
include_directories("${CMAKE_SOURCE_DIR}/ZGraphics/")
file(GLOB LED_CHECKER_SRC *.cpp *.h)
add_executable(LEDChecker ${LED_CHECKER_SRC} ${WRAP_FILES})
target_link_libraries(LEDChecker Qt5::Core Qt5::Widgets)
target_link_libraries(LEDChecker ZGraphics)
target_link_libraries(LEDChecker LEDAlgrithm)
LinkOpencv(LEDChecker)

AddTarget(LEDChecker)