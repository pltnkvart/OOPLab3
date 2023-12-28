cmake_minimum_required(VERSION 3.24)
project(Lab3)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(components/echelon)
add_subdirectory(components/fighters)
add_subdirectory(components/weapons)
add_subdirectory(template)

add_executable(Lab3 main.cpp)

#find_package(nlohmann_json 3.11.3 REQUIRED)
#nlohmann_json::nlohmann_json

target_link_libraries(Lab3 fighters weapons table echelon)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Our Project
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)
add_compile_options(-fsanitize=thread -fsanitize=thread -fPIE -pie -g)
add_link_options(-fsanitize=thread)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
