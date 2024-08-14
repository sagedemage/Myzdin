cmake_minimum_required(VERSION 3.22 VERSION 0.1.0)

project(Myzdin)

set(HEADER_FILES src/pch/myzdin-pch.h)

file(GLOB_RECURSE SOURCE_FILES "src/*.c")

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(STANDARD_C_VERSION_FLAG "-ansi")
set(OPTIMIZE_FLAG "-O3")
set(WARNING_FLAGS "-Werror -Wpedantic -Wall -Wextra")
set(DEBUG_FLAGS "-g")

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY lint_codebase.sh DESTINATION ${CMAKE_BINARY_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${STANDARD_C_VERSION_FLAG} ${OPTIMIZE_FLAG} ${WARNING_FLAGS} ${DEBUG_FLAGS}")

add_executable(Myzdin ${SOURCE_FILES})

target_link_libraries(Myzdin -lSDL2 -lSDL2_mixer -lSDL2_image)

target_precompile_headers(Myzdin PRIVATE ${HEADER_FILES})
