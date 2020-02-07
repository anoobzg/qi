
file(GLOB LED_ALGRITHM_SRC *.cpp *.h)

IncludeOpenCV()
add_definitions("-DLED_ALGRITHM_EXPORT")
add_library(LEDAlgrithm SHARED ${LED_ALGRITHM_SRC})
target_link_libraries(LEDAlgrithm BaseAlgrithm)
LinkOpencv(LEDAlgrithm)

AddTarget(LEDAlgrithm)