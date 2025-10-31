include(CTest)
include(Catch)

add_executable(test-Skywatcher Basic.cpp)
target_link_libraries(test-Skywatcher PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(test-Skywatcher)
