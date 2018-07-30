cmake_minimum_required(VERSION 3.12)
project(Nmail_client)

set(CMAKE_CXX_STANDARD 14)

add_executable(Nmail_client main.c mySocket.c mySocket.h client.c client.h)