cmake_minimum_required(VERSION 3.10.0)
project(cpp-dev VERSION 0.1.0 LANGUAGES C CXX)

add_executable(cpp-dev main.cpp tema1.cpp)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
