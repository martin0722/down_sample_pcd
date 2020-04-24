cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

add_definitions(-std=c++17)

project(down_sample_pcd)

find_package(PCL 1.2 REQUIRED)


include_directories(
    ${PCL_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIRS}
)
link_directories(
    ${PCL_LIBRARY_DIRS}  
)

add_definitions(${PCL_DEFINITIONS})

add_executable (down_sample_pcd src/main.cpp)
target_link_libraries (down_sample_pcd ${PCL_LIBRARIES} -lstdc++fs)
