cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)

project(MountEmulator)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

### Project Options
option(ME_BUILD_TEST "Build Tests." ON)

find_package(Threads REQUIRED)


### Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_DEBUG ON)
find_package(Boost 1.84 REQUIRED
    COMPONENTS program_options system json
)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost Libraries.")
endif()


add_subdirectory(lib)
add_subdirectory(tools)
if(ME_BUILD_TEST)
    add_subdirectory(test)
endif()
