file(GLOB SRCS "*.c" "*.cpp")
file(GLOB PUBLIC_HEADERS "*.h")

set(QUAZIP_LIB_VERSION 1.0.0)
set(QUAZIP_LIB_SOVERSION 1)

qt_wrap_cpp(MOC_SRCS ${PUBLIC_HEADERS})
set(SRCS ${SRCS} ${MOC_SRCS})

set(QUAZIP_TEST quazip_test)
add_executable(${QUAZIP_TEST} ${SRCS} ${PUBLIC_HEADERS})
target_link_libraries(${QUAZIP_TEST} ${QUAZIP_LIB_TARGET_NAME})
target_link_libraries(${QUAZIP_TEST} Qt5::Widgets Qt5::Network Qt5::Test)
LinkQuaZip(${QUAZIP_TEST})

AddTarget(${QUAZIP_TEST})

LinkZlib(${QUAZIP_TEST})
