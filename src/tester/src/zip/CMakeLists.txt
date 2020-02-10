include(LinkOpencv)
include(LinkZlib)

IncludeOpencv()
IncludeZlib()

set(EXE_NAME test_matzip)
file(GLOB SRC *.h *.cpp)
add_executable(${EXE_NAME} ${SRC})

LinkOpencv(${EXE_NAME})
LinkZlib(${EXE_NAME})

AddTarget(${EXE_NAME})