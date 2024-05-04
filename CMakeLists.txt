cmake_minimum_required(VERSION 3.27)
project(pvz)
set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)
add_subdirectory(src)

