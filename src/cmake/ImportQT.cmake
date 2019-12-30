set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set( QT5_ROOT_PATH CACHE PATH "Qt5 root directory (i.e. where the 'bin' folder lies)" )
if ( QT5_ROOT_PATH )
	list( APPEND CMAKE_PREFIX_PATH ${QT5_ROOT_PATH} )
endif()

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5PrintSupport)
find_package(Qt5Concurrent)
find_package(Qt5OpenGL)
find_package(Qt5OpenGLExtensions)	

include_directories(${Qt5OpenGL_INCLUDE_DIRS}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${Qt5Concurrent_INCLUDE_DIRS}
                    ${Qt5PrintSupport_INCLUDE_DIRS}
					)