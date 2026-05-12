cmake_minimum_required(VERSION 3.16)
project(tomasulo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Core
file(GLOB CORE_SRC src/core/*.cpp)
add_library(core ${CORE_SRC}
    include/core/global.h)
target_include_directories(core PUBLIC include)

# IO
file(GLOB IO_SRC src/io/*.cpp)
add_library(io ${IO_SRC})
target_include_directories(io PUBLIC include)

# Parser
file(GLOB PARSER_SRC src/parser/*.cpp)
add_library(parser ${PARSER_SRC})
target_include_directories(parser PUBLIC include)

# Reporting
file(GLOB REPORTING_SRC src/reporting/*.cpp)
add_library(reporting ${REPORTING_SRC})
target_include_directories(reporting PUBLIC include)

# Simulation
file(GLOB SIM_SRC src/simulation/*.cpp)
add_library(simulation ${SIM_SRC})
target_include_directories(simulation PUBLIC include)

# Main Executable
add_executable(simulator src/main.cpp)

target_link_libraries(simulator PRIVATE
    core
    io
    parser
    reporting
    simulation
)