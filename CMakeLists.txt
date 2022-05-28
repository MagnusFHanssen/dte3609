project(GameApp)
cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARIES})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARIES})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)



set( INCLUDE
        include/Landscape.hpp
	include/Camera.hpp
	include/Clock.hpp
	include/FpsCounter.hpp
	include/GameManager.hpp
	include/Input.hpp
	include/SceneObject.hpp
        include/Character.hpp
)
set( SRCS
        src/Landscape.cpp
	src/Camera.cpp
	src/GameManager.cpp
	src/SceneObject.cpp
        src/Character.cpp
	
	app/main.cpp
)

add_executable(${PROJECT_NAME} ${INCLUDE} ${SRCS})

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
