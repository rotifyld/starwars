cmake_minimum_required(VERSION 3.12)
project(starwars)

set(CMAKE_CXX_STANDARD 17)

add_executable(starwars starwars_example.cc rebelfleet.h imperialfleet.h battle.h)