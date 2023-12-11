add_library(table STATIC table.cpp table.h)

target_include_directories(table PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})