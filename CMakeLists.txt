cmake_minimum_required(VERSION 3.25)
project(NewFiles)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc)

add_executable(NewFiles
        inc/City.h
        inc/Human.h
        inc/Organism.h
        inc/Zombie.h
        src/City.cpp
        src/Human.cpp
        src/main.cpp
        src/Organism.cpp
        src/Zombie.cpp inc/GameSpecs.h)
