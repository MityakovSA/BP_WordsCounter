cmake_minimum_required(VERSION 3.5.1)
project(BP_WordCounter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.62.0 COMPONENTS system REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(BP_WordCounter main.cpp)
    target_link_libraries(BP_WordCounter ${Boost_LIBRARIES})
endif()