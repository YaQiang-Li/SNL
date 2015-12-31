cmake_minimum_required(VERSION 3.2)
project(SNL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    net/Epoll.cpp
    net/Epoll.hpp
    net/EventLoop.cpp
    net/EventLoop.hpp
    net/main.c)

add_executable(SNL ${SOURCE_FILES} net/EventDefine.h net/TcpConnection.cpp net/TcpConnection.h net/test.h net/test.cpp net/TcpServer.cpp net/TcpServer.h net/TcpServer.cpp net/TcpServer.h)