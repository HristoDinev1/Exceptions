cmake_minimum_required(VERSION 3.14)
project(BankingSystem CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(BANKING_SOURCES
    src/Application.cpp
    src/Menu.cpp
    src/BankSystem.cpp
    src/Account.cpp
    src/Transaction.cpp
    src/FileManager.cpp
    src/Statistics.cpp
    src/MyString.cpp
)

# Shared library used by the executable and the tests
add_library(banking_lib STATIC ${BANKING_SOURCES})
target_include_directories(banking_lib PUBLIC ${CMAKE_SOURCE_DIR}/inc)

# Main executable
add_executable(banking src/main.cpp)
target_link_libraries(banking PRIVATE banking_lib)

enable_testing()
add_subdirectory(tests)
