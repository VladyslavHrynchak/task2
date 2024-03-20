cmake_minimum_required(VERSION 2.8) 


project(task2)

# Set C compiler to GCC
set(CMAKE_C_COMPILER gcc)

# Set C++ compiler to G++
set(CMAKE_CXX_COMPILER g++)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/DLL/libgcc_s_seh-1.dll
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/DLL/libstdc++-6.dll
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/DLL/libwinpthread-1.dll
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(task2 main.cpp)

