add_library(echelon STATIC
        ../echelon/Echelon.h
        ../echelon/Echelon.cpp)

target_include_directories(echelon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
