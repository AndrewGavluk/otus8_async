cmake_minimum_required(VERSION 3.2)

add_library(queue STATIC queue.cpp queue.h)
add_library(printer STATIC printer.cpp printer.h)
add_library(consolePrinter STATIC ConsolePrinter.cpp ConsolePrinter.h)
add_library(filePrinter STATIC FilePrinter.cpp FilePrinter.h)
add_library(libinterpret STATIC lib_interpret.cpp lib_interpret.h)
add_library(asyncLib STATIC asyncLib.cpp asyncLib.h)
#set_target_properties(libinterpret  PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
#target_include_directories(libinterpret PRIVATE ${CMAKE_BINARY_DIR})

#add_library(libprinter STATIC printer.cpp printer.h FilePrinter.cpp FilePrinter.h ConsolePrinter.cpp ConsolePrinter.h)
#set_target_properties(libprinter  PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

#target_include_directories(libprinter PRIVATE ${CMAKE_BINARY_DIR})



#if(MSVC)
#	target_compile_options(libinterpret PRIVATE /W4)
#else()
# 	target_compile_options(libinterpret PRIVATE -Wall -Wextra -Werror)
#endif()
