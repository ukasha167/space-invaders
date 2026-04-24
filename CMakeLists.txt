cmake_minimum_required(VERSION 3.24)
project(main C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0135 NEW)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# FORCE RELEASE MODE
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# APPLY BASELINE OPTIMIZATIONS
if(MSVC)
    # Standard Release Optimization
    add_compile_options(/O2)
else()
    # Standard Release Optimization
    add_compile_options(-O2)
endif()

# ADDING RAYLIB
include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.0
)

FetchContent_MakeAvailable(raylib)

# SOURCE FILES
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.c")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

# EXECUTABLES
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
