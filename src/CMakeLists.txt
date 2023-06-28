set(CMAKE_CXX_STANDARD 11)
project(rogue)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

file(GLOB SOURCES "*.c*" "*.h*")

add_executable (${PROJECT_NAME} ${SOURCES})
target_link_libraries (${PROJECT_NAME} ${CURSES_LIBRARIES})