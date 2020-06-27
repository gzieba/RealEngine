cmake_minimum_required(VERSION 3.5)

project(RealEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES   "source/*.cpp")
file(GLOB_RECURSE HEADERS   "source/*.h")

link_directories(RealEngine PUBLIC lib)

add_executable(RealEngine ${SOURCES} ${HEADERS})

target_include_directories(RealEngine PUBLIC include source)

if(UNIX)
    target_link_libraries(RealEngine glfw3 assimp glad pthread X11 ${CMAKE_DL_LIBS})
endif()
if(WIN32)
    target_link_libraries(RealEngine glfw3 assimp glad)
endif()


