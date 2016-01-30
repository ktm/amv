set(CMAKE_CXX_COMPILER "/usr/local/bin/clang++")
set(CMAKE_C_COMPILER "/usr/local/bin/clang")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -ldl")

cmake_minimum_required(VERSION 3.3)

project(amvmodel)

include_directories(/usr/local/v8)
LINK_DIRECTORIES(/usr/local/v8/lib)

set(SOURCE_FILES test/test.cpp test/ProcessTest.hxx src/model/process_node.hxx src/model/process.hxx src/model/event.hxx src/model/context.hxx src/collection/name_value_pair.hxx test/ContextTest.hxx src/model/event_callback_container.hxx test/EventCallbackTest.h test/jstest.h)

add_executable(amvmodel ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(amvmodel v8 libv8_libplatform.a)
