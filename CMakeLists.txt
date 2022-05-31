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

find_package(assimp CONFIG REQUIRED)

add_custom_target(copy-resource-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_BINARY_DIR}/resources
    DEPENDS ${MY_TARGET})


set( INCLUDE
        include/Landscape.hpp
	include/Camera.hpp
	include/Clock.hpp
	include/FpsCounter.hpp
	include/GameManager.hpp
	include/Input.hpp
	include/SceneObject.hpp
        include/Character.hpp
        include/Billboard.hpp
        include/Particle.hpp
        include/Text.hpp
        include/ColSphereBody.hpp
        include/Minimap.hpp
        include/Shader.hpp
        include/Skybox.hpp
        include/Mesh.hpp
        include/Model.hpp
        include/Rock.hpp

        include/MyVertex.h
        include/ObjLoader.hpp

        include/glext.h
)
set( SRCS
        src/Landscape.cpp
	src/Camera.cpp
	src/GameManager.cpp
	src/SceneObject.cpp
        src/Character.cpp
        src/Billboard.cpp
        src/Particle.cpp
        src/Text.cpp
        src/Minimap.cpp
        src/Shader.cpp
        src/Skybox.cpp
        src/Mesh.cpp
        src/Model.cpp
        src/Rock.cpp
	
	app/main.cpp
)

add_executable(${PROJECT_NAME} ${INCLUDE} ${SRCS})

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} assimp::assimp)
