cmake_minimum_required(VERSION 3.2)

add_library(printer printer.h printer.cpp)
set_target_properties(printer PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(printer PRIVATE ${CMAKE_BINARY_DIR})

add_library(filePrinter FilePrinter.h FilePrinter.cpp)
set_target_properties(filePrinter PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(filePrinter PRIVATE ${CMAKE_BINARY_DIR})

add_library(consolePrinter ConsolePrinter.h ConsolePrinter.cpp)
set_target_properties(consolePrinter PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(consolePrinter PRIVATE ${CMAKE_BINARY_DIR})

add_library(libinterpret STATIC lib_interpret.cpp lib_interpret.h)
set_target_properties(printer libinterpret  PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(libinterpret PRIVATE ${CMAKE_BINARY_DIR})

add_library(libasync STATIC asyncLib.cpp asyncLib.h)
set_target_properties(libasync  PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(libasync PRIVATE ${CMAKE_BINARY_DIR})

if(MSVC)
	target_compile_options(libinterpret PRIVATE /W4)
else()
 	target_compile_options(libinterpret PRIVATE -Wall -Wextra -Werror)
endif()
