cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
set(Platform "")

set(STATIC_SFML TRUE)
set(BUILD_SHARED_LIBS FALSE)
add_definitions(-DSFML_STATIC)

add_definitions(-DDEBUG)

if (WIN32 AND NOT MINGW)
    set(Platform "win32")
elseif (WIN32 AND MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
    set(Platform "mingw")
elseif (APPLE)
    set(Platform "macos")
elseif (UNIX)
    set(Platform "mingw")
endif()

add_subdirectory(extlibs/Lua lua)
add_subdirectory(extlibs/SFML sfml)

include_directories(include)
include_directories(include/imgui)
include_directories(extlibs/Lua/src)
include_directories(include/MetaStuff)
include_directories(extlibs/SFML/include)

file(GLOB src src/*)
file(GLOB imgui src/imgui/*)
file(GLOB editor src/editor/*)

add_executable(untitled ${src} ${imgui} ${editor})

target_link_libraries(untitled lualib
        sfml-audio
        sfml-system
        sfml-window
        sfml-network
        sfml-graphics)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${Platform})

message("\nPlatform \t" ${Platform})
message("OutPath \t" ${EXECUTABLE_OUTPUT_PATH} "\n")