cmake_minimum_required(VERSION 3.21)
project(worktest-sdk)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(worktest-sdk SHARED source/library.cpp)

enable_testing()

add_executable(tests tests/test_main.cpp)

target_link_libraries(tests worktest-sdk GTest::gtest_main)

include(GoogleTest)