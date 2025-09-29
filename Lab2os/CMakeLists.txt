cmake_minimum_required(VERSION 3.15)
project(OsLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(OsLab Main.cpp thread_functions.cpp thread_functions.h)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тесты
add_executable(OsLab_tests tests.cpp thread_functions.cpp thread_functions.h)
target_link_libraries(OsLab_tests gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(OsLab_tests)
