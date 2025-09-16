# CMake version requirement
cmake_minimum_required(VERSION 3.16)

# Project name and version (Names the project)
project(BacktesterEngine VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags for better debugging and optimization
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include directories (where to find .h files)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect all source files into one
file(GLOB_RECURSE CORE_SOURCES 
    "src/core/*.cpp"
    "src/data/*.cpp" 
    "src/portfolio/*.cpp"
    "src/strategies/*.cpp"
)

# Create separate libraries for each component (basically adding the cpp into a library to use later)
add_library(backtester_data src/data/market_data.cpp)  
add_library(backtester_portfolio 
    src/portfolio/trade.cpp
    src/portfolio/position.cpp
    src/portfolio/portfolio.cpp
)
add_library(backtester_strategies 
    src/strategies/sma_crossover_strategy.cpp
    src/strategies/rsi_strategy.cpp
)

# Main executable links to libraries (builds the final product)
add_executable(backtester src/core/main.cpp)

#connects (telling your final product that it can use the other library)
target_link_libraries(backtester 
    backtester_data 
    backtester_portfolio
    backtester_strategies
)
# Optional: Print what we're building (helpful for debugging)
message(STATUS "Building BacktesterEngine v${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source files found: ${CORE_SOURCES}")

# Optional: Enable testing (when tests directory exists)
# enable_testing()
# add_subdirectory(tests)
