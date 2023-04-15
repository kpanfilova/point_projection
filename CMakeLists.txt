cmake_minimum_required(VERSION 3.22)
SET(PROJECTNAME point_projection)
PROJECT(${PROJECTNAME})
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

FILE(GLOB_RECURSE MY_HEADERS "include/*.hpp")
FILE(GLOB MY_SOURCES "src/*.cpp")

add_executable(${PROJECTNAME} point_projection.cpp ${MY_SOURCES} ${MY_HEADERS})

target_link_libraries(${PROJECTNAME} ${OpenCV_LIBS} )