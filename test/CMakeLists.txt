cmake_minimum_required(VERSION 3.2)

add_library(testPrinter TestPrinter.h TestPrinter.cpp)
set_target_properties(testPrinter PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(testPrinter PRIVATE ${CMAKE_BINARY_DIR})

enable_testing()

find_package(GTest REQUIRED)
include_directories()
add_executable(gtest_interpret test_interpret.cpp)

set_target_properties(gtest_interpret 
	PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})
				
if(MSVC)
	target_compile_options(gtest_interpret PRIVATE /W4)
else()
	target_compile_options(gtest_interpret PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
							
target_link_libraries(gtest_interpret gtest pthread printer filePrinter consolePrinter testPrinter libinterpret libasync )
							
add_test(gtest_interpret_test1 gtest_interpret)
