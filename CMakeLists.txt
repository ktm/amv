cmake_minimum_required(VERSION 3.3)
project(amvmodel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test/test.cpp test/ProcessTest.hxx src/model/process_node.hxx src/model/process.hxx src/model/event.hxx)
add_executable(amvmodel ${SOURCE_FILES})