cmake_minimum_required (VERSION 3.0)


# Library variables
set(LIBVETULUS_NAME vetulus)
set(LIBVETULUS_VERSION 0.1.0)



# Project name, version and description
project (${LIBVETULUS_NAME} VERSION ${LIBVETULUS_VERSION} LANGUAGES CXX DESCRIPTION "Vetulus services library")


# Use GNU way of install paths
include(GNUInstallDirs)


# Adds shared library to be compiled
add_library(${LIBVETULUS_NAME} SHARED config.cc)


# Sets library properties
set_target_properties(${LIBVETULUS_NAME} PROPERTIES
    VERSION ${LIBVETULUS_VERSION}
    SOVERSION 1
    PUBLIC_HEADER config.h
)



# Sets dynamic configuration file
configure_file(${LIBVETULUS_NAME}.pc.in ${LIBVETULUS_NAME}.pc @ONLY)


# Include current directory to library
target_include_directories(${LIBVETULUS_NAME} PRIVATE .)


# Installation instructions
install(TARGETS ${LIBVETULUS_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/vetulus
)


# Installation using pkgconfig
install(FILES ${CMAKE_BINARY_DIR}/${LIBVETULUS_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)



#
# Builds test binary for config module
#


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# Target binary
add_executable(test_vetulus_config config.cc test_config.cc)


# Links binary with Google Test library
target_link_libraries(test_vetulus_config gtest)


# Links binary with pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(test_vetulus_config Threads::Threads)
