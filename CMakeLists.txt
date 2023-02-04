cmake_minimum_required (VERSION 3.25.1)

project(digimonevotool)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(${PROJECT_NAME} digimonevotool.c)

target_compile_options(${PROJECT_NAME} PRIVATE
  -Wextra -Wpedantic -Werror -Wall -Wshadow -fno-strict-aliasing -std=c17 -O2
  )
include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY}
                             ${SDL2_IMAGE_LIBRARY})
