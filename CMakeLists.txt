cmake_minimum_required(VERSION 3.10)

# Set the project name
project(C_PLUS_PLUS_TOPICS VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# List the source files
set(SOURCES
    main.cpp
    ThreadPool/ThreadPool.cpp
    Scheduler/Scheduler.cpp
    ThreadSafeElements/ThreadJoiner.cpp
    Matrix/Matrix.cpp
    Logger/Logger.cpp
)

# Add the executable target
add_executable(C_PLUS_PLUS_TOPICS ${SOURCES})

# Include the directory with the header files
target_include_directories(C_PLUS_PLUS_TOPICS PRIVATE ${PROJECT_SOURCE_DIR})
