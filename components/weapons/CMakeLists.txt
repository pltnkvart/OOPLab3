add_library(weapons STATIC
        gun/Gun.cpp
        gun/gun.h
        rocket/RocketLauncher.cpp
        rocket/rocketLauncher.h
        projectile.h
        Weapon.h
        weaponType.h)

target_include_directories(weapons PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})