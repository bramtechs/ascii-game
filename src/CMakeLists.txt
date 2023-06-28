set(CMAKE_CXX_STANDARD 17)
project(rogue)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

add_compile_options(-Wall -Wextra -Wpedantic -ggdb)

file(GLOB SOURCES "*.c*" "*.h*")

add_executable (${PROJECT_NAME} ${SOURCES})
target_link_libraries (${PROJECT_NAME} ${CURSES_LIBRARIES})
