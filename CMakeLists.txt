cmake_minimum_required(VERSION 2.6)
add_subdirectory(test)
project(Clientapp)

add_executable(Clientapp client.cpp)

target_link_libraries(Clientapp pthread)