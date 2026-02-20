cmake_minimum_required(VERSION 3.10)

project(mcvrp LANGUAGES CXX)

set(LEMON_INCLUDE_DIR "$ENV{HOME}/lemon/include")
set(LEMON_LIBRARY "$ENV{HOME}/lemon/lib/libemon.a")

include(FetchContent)
FetchContent_Declare(
    json
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

add_executable(mcvrp
    src/main.cpp
    src/parser/json_parser.cpp
    src/graph/graph.cpp
    src/solver/solver.cpp
)


target_include_directories(mcvrp PRIVATE ${LEMON_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(mcvrp PRIVATE ${LEMON_LIBRARY} nlohmann_json::nlohmann_json)

add_executable(scenario1 
    src/experiments/scenario1.cpp
    src/parser/json_parser.cpp
    src/graph/graph.cpp
    src/solver/solver.cpp
    src/experiments/test_runner.cpp
)
target_include_directories(scenario1 PRIVATE ${LEMON_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(scenario1 PRIVATE ${LEMON_LIBRARY} nlohmann_json::nlohmann_json)

add_executable(scenario3
    src/experiments/scenario3.cpp
    src/parser/json_parser.cpp
    src/graph/graph.cpp
    src/solver/solver.cpp
    src/utils/edge_filters.cpp
    src/experiments/test_runner.cpp
)
target_include_directories(scenario3 PRIVATE ${LEMON_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(scenario3 PRIVATE ${LEMON_LIBRARY} nlohmann_json::nlohmann_json)
