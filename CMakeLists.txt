cmake_minimum_required(VERSION 3.11)

project(my_hash_table CXX)

set(CMAKE_CXX_STANDARD 23)

# ����������� ��������� ��� ����������� Visual Studio
if(MSVC)
    # ���������� ����������� �������� ��� ������������ ���������
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

    # �������� ������� ������� ��������������
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# ��������� ����������
add_library(my_hash_table SHARED "include/hash_table/hash_table.h" "src/hash_table.cpp")
target_include_directories(my_hash_table PUBLIC "include")

# ���������� googletest
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/6b63c98ac43efc992122f1da12aaf0a0e0658206.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ��������� �����
add_executable(hash_table_tests "tests/hash_table_tests.cpp")
target_link_libraries(hash_table_tests my_hash_table GTest::gtest_main)