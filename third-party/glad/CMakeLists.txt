cmake_minimum_required(VERSION 3.5)

project(glad LANGUAGES C)

file(GLOB SOURCE "glad.c")

add_library(glad ${SOURCE} ${HEADER})

target_include_directories(glad PUBLIC include)
