project(JPP_lista3_zad1)
cmake_minimum_required(VERSION 3.10)

include_directories(inc)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(MY_COMPILE_FLAGS -Wall -Wextra -pedantic -ansi)

#add_library(MyField STATIC inc/Field.hpp inc/FiniteModField.hpp src/FiniteModField.cpp)
#target_compile_options(MyField PRIVATE ${MY_COMPILE_FLAGS})
add_executable(zad1 app/main.cpp inc/FiniteModField.hpp src/FiniteModField.tpp)
target_compile_options(zad1 PRIVATE ${MY_COMPILE_FLAGS})
#target_link_libraries(zad1 PRIVATE MyField)