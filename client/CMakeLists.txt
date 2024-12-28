cmake_minimum_required(VERSION 3.31)

project(SocialApp-client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
  SocialApp-client
  main.cpp
  socialui.h
  socialui.cpp
  client.h client.cpp
)

target_compile_features(SocialApp-client PRIVATE cxx_std_23)

target_include_directories(SocialApp-client PRIVATE /usr/include/mysql)

target_link_libraries(SocialApp-client PRIVATE /usr/lib/libmysqlpp.so)
