cmake_minimum_required(VERSION 3.8)
project(nmp25)

enable_testing()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -lpthread)
endif()

foreach(IDX RANGE 1 3 1)
	add_executable(Question-${IDX}-out Question-${IDX}/Question-${IDX}.cc)
	target_link_libraries(Question-${IDX}-out pthread)
	add_test(question-${IDX} Question-${IDX}-out)
endforeach()


# Question 4: Extension Task. You need to integrate Google Tests here

# download n add google test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)
add_executable(Question-4-out Question-4/Question-4.cc)
target_link_libraries(Question-4-out gtest gtest_main gmock pthread)
add_test(question-4 Question-4-out)
