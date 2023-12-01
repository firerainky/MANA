cmake_minimum_required(VERSION 3.22)
project(OpenSSLExample)

include(ExternalProject)

# Set the version of OpenSSL to use
set(OPENSSL_VERSION "3.0.2")

# Set the path to download and build OpenSSL
set(OPENSSL_SOURCE_DIR ${CMAKE_BINARY_DIR}/openssl-source)
set(OPENSSL_BUILD_DIR ${CMAKE_BINARY_DIR}/openssl-build)
set(OPENSSL_INSTALL_DIR ${CMAKE_BINARY_DIR}/openssl-install)

# Download and build OpenSSL as an external project
ExternalProject_Add(
    OpenSSLExternalProject
    PREFIX ${OPENSSL_BUILD_DIR}
    URL https://www.openssl.org/source/openssl-${OPENSSL_VERSION}.tar.gz
    SOURCE_DIR ${OPENSSL_SOURCE_DIR}
    BINARY_DIR ${OPENSSL_BUILD_DIR}
    CONFIGURE_COMMAND ${OPENSSL_SOURCE_DIR}/config --prefix=${OPENSSL_INSTALL_DIR} shared
    BUILD_COMMAND make
    INSTALL_COMMAND ""
)

# Add OpenSSL as a dependency for the main executable
add_executable(MyExecutable main.cpp)
add_dependencies(MyExecutable OpenSSLExternalProject)

# Specify include directories and link against OpenSSL
target_include_directories(MyExecutable PRIVATE ${OPENSSL_INSTALL_DIR}/include)
target_link_libraries(MyExecutable PRIVATE libcrypto)
