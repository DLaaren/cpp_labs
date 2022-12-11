cmake_minimum_required(VERSION 3.0.0)
project(tamagochi)

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_MIXER REQUIRED)


if (NOT DEFINED SDL2_INCLUDE_DIR)
  if (DEFINED SDL2_INCLUDE_DIRS)
    set(SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIRS})
  endif()
endif()
if (NOT DEFINED SDL2_IMAGE_INCLUDE_DIR)
  if (DEFINED SDL2_IMAGE_INCLUDE_DIRS)
    set(SDL2_IMAGE_INCLUDE_DIR ${SDL2_IMAGE_INCLUDE_DIRS})
   endif()
endif()
if (NOT DEFINED SDL2_MIXER_INCLUDE_DIR)
  if (DEFINED SDL2_MIXER_INCLUDE_DIRS)
    set(SDL2_MIXER_INCLUDE_DIR ${SDL2_MIXER_INCLUDE_DIRS})
   endif()
endif()


include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
include_directories(gamebase)



set(SOURCES
   ${PROJECT_SOURCE_DIR}/main.cpp
   ${PROJECT_SOURCE_DIR}/gamebase/tamagochi.h
   ${PROJECT_SOURCE_DIR}/gamebase/game.h
   ${PROJECT_SOURCE_DIR}/gamebase/game.cpp
   ${PROJECT_SOURCE_DIR}/gamebase/textureManager.h
   ${PROJECT_SOURCE_DIR}/gamebase/textureManager.cpp
   ${PROJECT_SOURCE_DIR}/gamebase/gameObject.h
   ${PROJECT_SOURCE_DIR}/gamebase/gameObject.cpp
   )

add_executable(${PROJECT_NAME} ${SOURCES})


if (NOT DEFINED SDL2_LIBRARIES)
  set(SDL2_LIBRARIES "SDL2::SDL2")
endif()

if (NOT DEFINED SDL2_IMAGE_LIBRARIES)
  set(SDL2_IMAGE_LIBRARIES "SDL2_image::SDL2_image")
endif()

if (NOT DEFINED SDL2_MIXER_LIBRARIES)
  set(SDL2_MIXER_LIBRARIES "SDL2_mixer::SDL2_mixer")
endif()


target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)