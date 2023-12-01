cmake_minimum_required(VERSION 3.22)
project(directly_openssl)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Specify the path to the binary package
set(PACKAGE_PATH "external")

# Add include directories for the binary package
include_directories(${PACKAGE_PATH}/include)

# Add library directories for the binary package
link_directories(${PACKAGE_PATH})

# Create your executable
add_executable(MyExecutable main.cpp)

# Link against the libraries from the binary package
target_link_libraries(MyExecutable
    PRIVATE
    crypto
    # Add more libraries as needed
)