cmake_minimum_required(VERSION 4.0)
project(ds)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(ds test.cpp
        LinkedList.cpp
        LinkedList.h
        vector.cpp
        vector.h)

target_link_libraries(
        ds
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ds)
