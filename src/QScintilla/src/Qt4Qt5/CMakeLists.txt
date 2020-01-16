
file(GLOB QT4Qt5_SRC *.h *.cpp)
file(GLOB QSci_HEADERS Qsci/*.h)
file(GLOB CORE_HEADERS ../include/*.h)
file(GLOB CORE_SRC ../src/*.h ../src/*.cpp)
file(GLOB LEX_SRC ../lexlib/*.h ../lexlib/*.cpp ../lexers/*.cpp)

add_definitions("-DQSCINTILLA_MAKE_DLL")

add_library(${QSCINTILLA_NAME} SHARED ${QT4Qt5_SRC} ${QSci_HEADERS} ${CORE_HEADERS} ${CORE_SRC} ${LEX_SRC})
target_link_libraries(${QSCINTILLA_NAME} Qt5::Widgets Qt5::PrintSupport)

AddTarget(${QSCINTILLA_NAME})
