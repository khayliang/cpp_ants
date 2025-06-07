cmake_minimum_required(VERSION 3.16)
project(cpp_ants)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# build game engine library
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/engine/*.cpp)
add_library(engine STATIC ${ENGINE_SOURCES})
target_include_directories(engine PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(engine PUBLIC sfml-graphics sfml-window sfml-system)

# build main executable
add_executable(cpp_ants src/main.cpp)
target_link_libraries(cpp_ants PRIVATE engine)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# build tests
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()  

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

add_executable(cpp_ants_tests ${TEST_SOURCES})

target_link_libraries(cpp_ants_tests
    PRIVATE
        GTest::gtest
        GTest::gtest_main
        engine
)

include(GoogleTest)
gtest_discover_tests(cpp_ants_tests)

function(set_testing_mode target)
    target_compile_definitions(${target} PRIVATE TESTING)
endfunction()

option(BUILD_TESTING "Enable tests" OFF)

if (BUILD_TESTING)
    set_testing_mode(engine)
    set_testing_mode(cpp_ants)
    set_testing_mode(cpp_ants_tests)
endif()