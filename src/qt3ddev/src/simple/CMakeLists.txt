set(PROJECT_NAME qt3d_dev_simple)
add_executable(${PROJECT_NAME} main.cpp scenemodifier.cpp)
target_link_libraries(${PROJECT_NAME} ${QT3D_All})
AddTarget(${PROJECT_NAME})