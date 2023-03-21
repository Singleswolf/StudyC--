cmake_minimum_required(VERSION 3.0.0)
project(StudyC++)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++11 support has been enabled by default.")

include(CTest)
enable_testing()

include_directories(include)

AUX_SOURCE_DIRECTORY(src SRC)

add_executable(StudyC++ ${SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
