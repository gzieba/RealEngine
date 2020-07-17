cmake_minimum_required(VERSION 3.10)

project(RealEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES   "source/*.cpp")
file(GLOB_RECURSE HEADERS   "source/*.h")
include(CMake/FileListImGui.txt)

link_directories(RealEngine PUBLIC lib)

add_executable(RealEngine ${SOURCES} ${HEADERS} ${IMGUI_SOURCE} ${IMGUI_HEADER})

target_include_directories(RealEngine PUBLIC source third-party/glad/include third-party/imgui)

if(UNIX)
    target_link_libraries(RealEngine glfw glad assimp pthread X11 ${CMAKE_DL_LIBS})
endif()
if(WIN32)
    target_link_libraries(RealEngine glfw glad assimp)
endif()
