cmake_minimum_required(VERSION 2.6)

# Name of project
set(PROJ_NAME Game)
project(${PROJ_NAME})

# Specify project files: header files and source files
set(HDRS
    src/game/engine/utilities/file_utils.h
    src/game/game.h
    src/game/utilities/util.h
    src/game/object/game_object.h
    src/game/object/effect_object.h
    src/game/object/collider.h
    src/game/entities/entity.h
    src/game/engine/shader/shader.h
    src/game/engine/audio/audio_manager.h
    src/game/entities/player_entity.h
    src/game/entities/enemy_entity.h
    src/game/object/colliders/circle_collider.h
    src/game/object/colliders/ray_collider.cpp
    src/game/object/follower_object.h
    src/game/entities/bullet.h
    src/game/object/interfaces/parent_entity.h
    src/game/entities/interfaces/shooter.h
    src/game/entities/collectible.h
    src/game/entities/collectibles/addshield.h
    src/game/entities/collectibles/rateoffire.h
    src/game/object/followers/orbiter.h
    src/game/engine/texture_library.h
    src/game/object/followers/shield.h
    src/game/entities/enemies/buoy.h
)
 
set(SRCS
    src/game/engine/utilities/file_utils.cpp
    src/game/game.cpp
    src/game/utilities/util.cpp
    src/game/object/game_object.cpp
    src/game/object/effect_object.cpp
    src/game/object/collider.cpp
    src/game/entities/entity.cpp
    src/main.cpp
    src/game/engine/shader/shader.cpp
    src/game/engine/audio/audio_manager.cpp
    src/game/entities/player_entity.cpp
    src/game/entities/enemy_entity.cpp
    src/game/object/colliders/circle_collider.cpp
    src/game/object/colliders/ray_collider.cpp
    src/game/object/follower_object.cpp
    src/game/entities/bullet.cpp
    src/game/object/interfaces/parent_entity.cpp
    src/game/entities/interfaces/shooter.cpp
    src/game/entities/collectible.cpp
    src/game/entities/collectibles/addshield.cpp
    src/game/entities/collectibles/rateoffire.cpp
    src/game/object/followers/orbiter.cpp
    src/game/engine/texture_library.cpp
    src/game/object/followers/shield.cpp
    src/game/entities/enemies/buoy.cpp
)

# Add path name to configuration file
configure_file(src/game/path_config.h.in path_config.h)

# Add executable based on the source files
add_executable(${PROJ_NAME} ${HDRS} ${SRCS})

# Directories to include for header files, so that the compiler can find
# path_config.h
target_include_directories(${PROJ_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Require OpenGL library
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJ_NAME} ${OPENGL_gl_LIBRARY})

# Other libraries needed
set(LIBRARY_PATH "" CACHE PATH "Folder with GLEW, GLFW, GLM, and SOIL libraries")
include_directories(${LIBRARY_PATH}/include)
if(NOT WIN32)
    find_library(GLEW_LIBRARY GLEW)
    find_library(GLFW_LIBRARY glfw)
    find_library(SOIL_LIBRARY SOIL)
    find_library(OPENAL_LIBRARY openal)
    find_library(ALUT_LIBRARY alut)
elseif(WIN32)
    find_library(GLEW_LIBRARY glew32s HINTS ${LIBRARY_PATH}/lib)
    find_library(GLFW_LIBRARY glfw3 HINTS ${LIBRARY_PATH}/lib)
    find_library(SOIL_LIBRARY SOIL HINTS ${LIBRARY_PATH}/lib)
    find_library(OPENAL_LIBRARY "OpenAL32.lib" HINTS ${LIBRARY_PATH}/lib)
    find_library(ALUT_LIBRARY "alut.lib" HINTS ${LIBRARY_PATH}/lib)
endif(NOT WIN32)
target_link_libraries(${PROJ_NAME} ${GLEW_LIBRARY})
target_link_libraries(${PROJ_NAME} ${GLFW_LIBRARY})
target_link_libraries(${PROJ_NAME} ${SOIL_LIBRARY})
target_link_libraries(${PROJ_NAME} ${OPENAL_LIBRARY})
target_link_libraries(${PROJ_NAME} ${ALUT_LIBRARY})

# The rules here are specific to Windows Systems
if(WIN32)
    # Avoid ZERO_CHECK target in Visual Studio
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(${PROJ_NAME} PROPERTIES DEBUG_POSTFIX _d)
endif(WIN32)