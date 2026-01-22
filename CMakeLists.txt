cmake_minimum_required(VERSION 3.10)
project(mcvrp LANGUAGES CXX)

# LEMON include and lib directories
set(LEMON_INCLUDE_DIR "$ENV{HOME}/lemon/include")
set(LEMON_LIBRARY "$ENV{HOME}/lemon/lib/libemon.a") # or liblemon.so if you built shared

# Add executable
add_executable(mcvrp src/main.cpp)

# Include headers
target_include_directories(mcvrp PRIVATE ${LEMON_INCLUDE_DIR})

# Link library
target_link_libraries(mcvrp PRIVATE ${LEMON_LIBRARY})
