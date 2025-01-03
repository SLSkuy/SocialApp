cmake_minimum_required(VERSION 3.31)

project(SocialApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
  YuzuServer
  main.cpp
  netizen.h
  netizen.cpp
  server.h
  server.cpp
  message.h
  dbcontrol.h
  dbcontrol.cpp)

target_compile_features(YuzuServer PRIVATE cxx_std_23)

target_include_directories(YuzuServer PRIVATE /usr/include/mysql)

target_link_libraries(YuzuServer PRIVATE /usr/lib/libmysqlpp.so)

install(TARGETS YuzuServer RUNTIME DESTINATION /usr/bin )
