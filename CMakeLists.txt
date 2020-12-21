cmake_minimum_required(VERSION 3.0.0)
project(shootTheVirus VERSION 0.0.1)

# uncomment to set verbose=1 for debug
# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(main main.c)

add_subdirectory(lib)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_include_directories(main PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib"
                          )
target_link_libraries(main PUBLIC lib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} X11 m)