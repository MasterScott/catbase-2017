cmake_minimum_required(VERSION 3.3)
project(catbase CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -fPIC -std=gnu++1z")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_definitions(
    -D_GLIBCXX_USE_CXX11_ABI=0 
    -D_LINUX=1 
    -DLINUX=1 
    -D_POSIX=1 
    -DPOSIX=1 
    -DRAD_TELEMETRY_DISABLED=1 
    -DUSE_SDL=1 
    -DGNUC=1 
    -DNO_MALLOC_OVERRIDE=1)

add_library(catbase SHARED ${SOURCES})

set(SOURCE_SDK_HEADERS source-sdk-2013-headers/mp/src)

include_directories(include)
include_directories(SYSTEM
    ${SOURCE_SDK_HEADERS}/public 
    ${SOURCE_SDK_HEADERS}/mathlib 
    ${SOURCE_SDK_HEADERS}/common 
    ${SOURCE_SDK_HEADERS}/public/tier0 
    ${SOURCE_SDK_HEADERS}/public/tier1
    ${SOURCE_SDK_HEADERS})

set_target_properties(catbase PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY "bin"
    OUTPUT_NAME "catbase"
    COMPILE_FLAGS "-m32"
    LINK_FLAGS "-m32")