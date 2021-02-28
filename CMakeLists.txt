cmake_minimum_required(VERSION 3.0)
project(Threads)

# Set the module path to include scripts
list(APPEND CMAKE_MODULE_PATH  ${Threads_SOURCE_DIR}/CMake)
include(Configure)

if (Threads_ExternalTarget)

    set(TargetFolders ${Threads_TargetFolders})
    set(TargetName    ${Threads_TargetName})
    set(TargetGroup   ${Threads_TargetGroup})
else()
    subdirs(CMake)

    set(TargetFolders FALSE)
    set(TargetName Threads)

    set(Threads_INCLUDE  ${Threads_SOURCE_DIR}/Source)
    set(Threads_LIBRARY  ${TargetName})

endif()

subdirs(Source)

if (Threads_BUILD_TEST)
    set(BUILD_GMOCK   OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

    subdirs(Test/googletest)
    subdirs(Test)
endif()
