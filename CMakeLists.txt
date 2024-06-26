cmake_minimum_required(VERSION 3.0)
project(main C)

# Find Ncurses package
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

# Find SQLite3 package
find_package(SQLite3 REQUIRED)

# Add executable
add_executable(main main.c)

# Link Ncurses and SQLite3 libraries
target_link_libraries(main ${CURSES_LIBRARIES} SQLite::SQLite3)
