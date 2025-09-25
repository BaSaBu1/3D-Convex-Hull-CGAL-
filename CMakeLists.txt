cmake_minimum_required(VERSION 3.12...3.29)
project(CGALTest)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "C:/Users/batsa/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Find CGAL library installed via vcpkg
find_package(CGAL REQUIRED)

# Create executable
add_executable(test test.cpp)

# Link CGAL libraries
target_link_libraries(test CGAL::CGAL)