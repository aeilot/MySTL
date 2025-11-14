cmake_minimum_required(VERSION 4.0)
project(my_stl)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(my_stl test.cpp
        include/array.h)

target_link_libraries(
        my_stl
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(my_stl)
