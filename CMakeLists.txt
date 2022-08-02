cmake_minimum_required(VERSION 3.21)
project(WackUtils)

set(CMAKE_CXX_STANDARD 20)

# Library {
    # Files {
        file(GLOB_RECURSE srcFiles "src/*")
        include_directories(${CMAKE_SOURCE_DIR}/include)
    # }

    # Add the files to the project.
    add_library(WackUtils STATIC ${srcFiles})

    # External libraries {
        find_package(cryptopp REQUIRED)
        find_package(CURL CONFIG REQUIRED)
        target_link_libraries(WackUtils PRIVATE CURL::libcurl cryptopp-static)
    # }
# }

# Target {
    # Add the target to the project.
    # Used for testing the networking, process, and window functions.
    add_executable(target target/main.cpp)
# }

# Testing {
    enable_testing()
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY "https://github.com/google/googletest"
            GIT_TAG        release-1.12.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(GoogleTest)
    include(GoogleTest)

    # add tests
    file(GLOB_RECURSE testsSrc "tests/*")
    add_executable(tests ${testsSrc})
    target_link_libraries(tests WackUtils gtest_main)
    gtest_discover_tests(tests)
# }