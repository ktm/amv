set(CMAKE_CXX_COMPILER "/usr/local/bin/clang++")
set(CMAKE_C_COMPILER "/usr/local/bin/clang")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -ldl -DCHAISCRIPT_NO_THREADS")

cmake_minimum_required(VERSION 3.3)
project(amvmodel)

set(SOURCE_FILES test/test.cpp
        test/ProcessTest.hxx
        src/model/process_node.hxx
        src/model/process.hxx
        src/model/event.hxx
        src/model/context.hxx
        src/collection/name_value_pair.hxx
        test/ContextTest.hxx
        src/model/event_callback_container.hxx
        test/EventCallbackTest.h
        test/jstest.h
        src/script/script_gateway.h
        src/script/chaiscript_gateway.h
        src/script/chaiscript_gateway.cpp
        src/serial/serial.h
        src/serial/serial.cpp
        src/gps/gps.h
        src/gps/gps.cpp
        src/gps/nmea.h
        src/gps/nmea.cpp)

add_executable(amvmodel ${SOURCE_FILES})
