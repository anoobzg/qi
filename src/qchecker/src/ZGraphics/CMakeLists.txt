
file(GLOB ZGRAPHICS_SRC *.cpp *.h)
add_definitions("-DZG_EXPORT")
add_library(ZGraphics SHARED ${ZGRAPHICS_SRC})
target_link_libraries(ZGraphics Qt5::Core Qt5::Gui Qt5::Widgets)
AddTarget(ZGraphics)