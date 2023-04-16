include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(unittests testPathSorting.cpp)
target_link_libraries(unittests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unittests)