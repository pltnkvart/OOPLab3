add_library(mission STATIC
        ../mission/Mission.cpp
        ../mission/Mission.h)

find_package(nlohmann_json 3.11.3 REQUIRED)
target_link_libraries(mission PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(mission PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../mission)