cmake_minimum_required(VERSION 3.26)
project(libant)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(.)

file(GLOB TEST_SOURCES "test/*.cpp")

add_executable(libant ${TEST_SOURCES})

target_link_libraries(
        libant
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(libant)
