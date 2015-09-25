set(CMAKE_CXX_COMPILER "/usr/local/bin/clang++")
set(CMAKE_C_COMPILER "/usr/local/bin/clang")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

cmake_minimum_required(VERSION 3.3)
project(amvmodel)


set(SOURCE_FILES test/test.cpp test/ProcessTest.hxx src/model/process_node.hxx src/model/process.hxx src/model/event.hxx src/model/context.hxx src/collection/name_value_pair.hxx test/ContextTest.hxx src/model/event_callback_container.hxx test/EventBusTest.h)
add_executable(amvmodel ${SOURCE_FILES})