add_library(echelon STATIC
        ../echelon/Echelon.h
        ../echelon/Echelon.cpp)

find_package(raylib ${RAYLIB_VERSION} QUIET)
target_link_libraries(echelon PRIVATE raylib)

target_include_directories(echelon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
