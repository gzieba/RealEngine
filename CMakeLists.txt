cmake_minimum_required(VERSION 3.10)

project(RealEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES   "source/*.cpp")
file(GLOB_RECURSE HEADERS   "source/*.h")
include(CMake/FileListImGui.txt)

link_directories(RealEngine PUBLIC lib)

add_executable(RealEngine ${SOURCES} ${HEADERS} ${IMGUI_SOURCE} ${IMGUI_HEADER})
add_library(ImGuiFileDialog STATIC
    ${CMAKE_SOURCE_DIR}/third-party/ImGuiFileDialog/ImGuiFileDialog.cpp
    ${CMAKE_SOURCE_DIR}/third-party/ImGuiFileDialog/ImGuiFileDialog.h)

target_include_directories(RealEngine PUBLIC source
                        third-party
                        third-party/assimp/include
                        third-party/glfw/include
                        third-party/glad/include
			third-party/imgui
			third-party/stb
			third-party/ImGuiFileDialog)
target_include_directories(ImGuiFileDialog PUBLIC third-party/imgui)

if(UNIX)
    target_link_libraries(RealEngine glfw3 glad assimp ImGuiFileDialog pthread X11 ${CMAKE_DL_LIBS})
endif()
if(WIN32)
    target_link_libraries(RealEngine glfw3 glad ImGuiFileDialog assimp)
endif()
