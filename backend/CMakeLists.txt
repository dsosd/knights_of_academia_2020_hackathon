cmake_minimum_required(VERSION 3.0)

project(hackathon/knights_of_acadamia_2020)

set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 14)

set(default_srcs ${default_srcs} src/main.cpp)
set(default_srcs ${default_srcs} src/arduino.cpp)
set(default_srcs ${default_srcs} src/keyboard.cpp)
set(default_srcs ${default_srcs} src/server.cpp)
add_executable(default ${default_srcs})

target_include_directories(default PRIVATE src PRIVATE include)

find_library(default_lib_temp httpserver PATHS lib NO_DEFAULT_PATH)
set(default_libs ${default_libs} ${default_lib_temp})
unset(default_lib_temp CACHE)

target_link_libraries(default ${default_libs})
