cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SOURCES "./*.c")

add_library(gui STATIC ${SOURCES})