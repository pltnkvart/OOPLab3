cmake_minimum_required(VERSION 3.24)
project(Lab3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab3 main.cpp
        components/fighters/Fighter.cpp
        components/fighters/camouflagedFighter/CamouflageFighter.cpp
        components/fighters/rebFighter/REBFighter.h
        components/fighters/radioFighter/RadioFighter.h
        components/fighters/proFighter/PROFighter.h
        components/echelon/Echelon.h
        components/echelon/Echelon.cpp
        components/weapons/Weapon.cpp
        components/weapons/rocket/rocketLauncher.h
        components/weapons/gun/gun.h
        components/weapons/gun/Gun.cpp
        components/weapons/rocket/RocketLauncher.cpp
        components/weapons/projectile.h
        components/fighters/proFighter/PROFighter.cpp
        components/fighters/radioFighter/RadioFighter.cpp
        components/fighters/rebFighter/REBFighter.cpp
        components/fighters/scoutFighter/ScoutFighter.cpp)
