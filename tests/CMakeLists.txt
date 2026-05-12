include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(public_tests public_tests.cpp)
target_link_libraries(public_tests PRIVATE banking_lib Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(public_tests)
