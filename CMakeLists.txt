cmake_minimum_required(VERSION 3.25)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
project(print_ip VERSION ${PROJECT_VESRION})

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

add_executable(
    print_ip 
    print_ip.cpp
)

add_executable(
    test_print_ip_gtest 
    test_print_ip_gtest.cpp
)

set_target_properties(
    print_ip
    test_print_ip_gtest
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(
    test_print_ip_gtest 
    PROPERTIES 
    COMPILE_DEFINITIONS 
    STATIC_LINK
)

target_link_libraries(
    test_print_ip_gtest 
    gtest 
    gtest_main
)

target_link_options(print_ip PRIVATE -static -static-libgcc -static-libstdc++)

target_link_options(test_print_ip_gtest PRIVATE -static -static-libgcc -static-libstdc++)

if (MSVC)
    target_compile_options(print_ip PRIVATE /W4)
    target_compile_options(test_print_ip_gtest PRIVATE /W4)
else ()
    target_compile_options(
        print_ip 
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
    )
    target_compile_options(
        test_print_ip_gtest 
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
    )
endif()

install (
    TARGETS 
    print_ip 
    RUNTIME 
    DESTINATION 
    bin
)

# CPack area
if (WIN32)
    set(CPACK_GENERATOR "ZIP")
else ()
    set(CPACK_GENERATOR "DEB")
endif()
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT https://github.com/4l3x777/homework1)
include(CPack)

# Tests area
enable_testing()

add_test(
    NAME 
    unit_tests_test_print_ip_gtest 
    COMMAND 
    test_print_ip_gtest
)
