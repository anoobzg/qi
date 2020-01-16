
include_directories("${CMAKE_SOURCE_DIR}/Qt4Qt5/")

qt5_add_resources(qrc_FILES application.qrc)
add_executable(${QSCINTILLA_NAME}-example main.cpp mainwindow.h mainwindow.cpp ${qrc_FILES})
target_link_libraries(${QSCINTILLA_NAME}-example ${QSCINTILLA_NAME})
AddTarget(${QSCINTILLA_NAME}-example)