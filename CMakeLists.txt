cmake_minimum_required(VERSION 3.27)
project(cql VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ==============================================================================
# Build flags

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
    "Choose the type of build (Debug, OptDebug, Release)" FORCE)
endif()

# Debug flags: enable debug symbols and disable optimization
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# OptDebug flags: enable debug symbols and enable optimization
set(CMAKE_CXX_FLAGS_OPTDEBUG "-g -O3")
set(CMAKE_CXX_FLAGS_OPTDEBUG "${CMAKE_CXX_FLAGS_OPTDEBUG} -DOPTDEBUG")

# Release flags: enable optimization
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Apply the selected build type's flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
# ==============================================================================

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.c
                               ${PROJECT_SOURCE_DIR}/src/metacommand/metacommand.c
                               ${PROJECT_SOURCE_DIR}/src/statements/parser.c
                               ${PROJECT_SOURCE_DIR}/src/runner/runner.c)
