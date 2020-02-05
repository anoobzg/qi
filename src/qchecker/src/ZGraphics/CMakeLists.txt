
file(GLOB ZGRAPHICS_SRC *.cpp *.h)
add_definitions("-DZG_EXPORT")
add_library(ZGraphics SHARED ${ZGRAPHICS_SRC})
target_link_libraries(ZGraphics PUBLIC Qt5::Core)
AddTarget(ZGraphics)