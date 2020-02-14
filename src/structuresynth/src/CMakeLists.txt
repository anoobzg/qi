cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(structuresynth)

set(QT_MIN_VERSION "5.6.1")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets Gui Xml Script)

file(GLOB ss_GUI StructureSynth/GUI/*.h StructureSynth/GUI/*.cpp)
file(GLOB ss_JavaScriptSupport StructureSynth/JavaScriptSupport/*.h StructureSynth/JavaScriptSupport/*.cpp)
file(GLOB ss_Model StructureSynth/Model/*.h StructureSynth/Model/*.cpp)
file(GLOB ss_Model_Rendering StructureSynth/Model/Rendering/*.h StructureSynth/Model/Rendering/*.cpp)
file(GLOB ss_Parser StructureSynth/Parser/*.h StructureSynth/Parser/*.cpp)

file(GLOB sc_Exceptions SyntopiaCore/Exceptions/*.h SyntopiaCore/Exceptions/*.cpp)
file(GLOB sc_GLEngine SyntopiaCore/GLEngine/*.h SyntopiaCore/GLEngine/*.cpp)
file(GLOB sc_GLEngine_Raytracer SyntopiaCore/GLEngine/Raytracer/*.h SyntopiaCore/GLEngine/Raytracer/*.cpp)
file(GLOB sc_Logging SyntopiaCore/Logging/*.h SyntopiaCore/Logging/*.cpp)
file(GLOB sc_Math SyntopiaCore/Math/*.h SyntopiaCore/Math/*.cpp)
file(GLOB sc_Misc SyntopiaCore/Misc/*.h SyntopiaCore/Misc/*.cpp)

file(GLOB tpc_MersenneTwister ThirdPartyCode/MersenneTwister/*.h)

qt5_add_resources(qrc_FILES StructureSynth.qrc)

include_directories("./")
add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_executable(structuresynth Main.cpp ${ss_GUI} ${ss_JavaScriptSupport} ${ss_Model} ${ss_Model_Rendering} ${ss_Parser}
							  ${sc_Exceptions} ${sc_GLEngine} ${sc_GLEngine_Raytracer} ${sc_Logging} ${sc_Math} ${sc_Misc}
							  ${tpc_MersenneTwister} ${qrc_FILES})
							  
target_link_libraries(structuresynth Qt5::Core Qt5::Widgets Qt5::Xml Qt5::Script)
target_link_libraries(structuresynth "opengl32.lib" "glu32.lib")

TopAddTarget(structuresynth)
ConfigureAll()