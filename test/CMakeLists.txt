cmake_minimum_required(VERSION 3.2)
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
							
target_link_libraries(gtest_interpret gtest pthread libinterpret)
							
add_test(gtest_interpret_test1 gtest_interpret)
