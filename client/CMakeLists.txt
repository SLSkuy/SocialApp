cmake_minimum_required(VERSION 3.31)

project(SocialApp-client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
  YuzuClient
  main.cpp
  socialui.h
  socialui.cpp
  client.h client.cpp
)

target_compile_features(YuzuClient PRIVATE cxx_std_23)

install(TARGETS YuzuClient RUNTIME DESTINATION /usr/bin )

