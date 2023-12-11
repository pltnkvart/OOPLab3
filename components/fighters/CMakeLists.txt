add_library(fighters STATIC
        camouflagedFighter/CamouflageFighter.cpp
        proFighter/PROFighter.cpp
        radioFighter/RadioFighter.cpp
        rebFighter/REBFighter.cpp
        scoutFighter/ScoutFighter.cpp
        Fighter.cpp
        Fighter.h)

target_include_directories(fighters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})