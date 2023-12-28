cmake_minimum_required(VERSION 3.24)
project(Tests)

set(CMAKE_CXX_STANDARD 20)

if(UNIX)
    set(gtest_source_url https://github.com/google/googletest/archive/release-1.11.0.tar.gz)
elseif(WIN32)
    set(gtest_source_url https://github.com/google/googletest/archive/release-1.11.0.zip)
else()
    message(FATAL_ERROR "Операционная система не поддерживается")
endif()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL ${gtest_source_url}
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_compile_options(--coverage)
add_link_options(--coverage)

include_directories(template)
#add_subdirectory(components/echelon)
#add_subdirectory(../components/fighters)
#add_subdirectory(components/weapons)
#add_subdirectory(components/mission)
#add_subdirectory(template)

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

add_executable(Tests test.cpp
        ../components/fighters/Fighter.cpp
        ../components/weapons/gun/Gun.cpp
        ../components/echelon/Echelon.cpp
        ../components/weapons/rocket/RocketLauncher.cpp
        ../template/table.cpp)

target_link_libraries(Tests gtest gtest_main raylib)