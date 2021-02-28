cmake_minimum_required(VERSION 3.0)
project(Template)

# Set the module path to include scripts
list(APPEND CMAKE_MODULE_PATH  ${Template_SOURCE_DIR}/CMake)
include(Configure)

if (Template_ExternalTarget)

    set(TargetFolders ${Template_TargetFolders})
    set(TargetName    ${Template_TargetName})
    set(TargetGroup   ${Template_TargetGroup})
else()
    subdirs(CMake)

    set(TargetFolders FALSE)
    set(TargetName Template)

    set(Template_INCLUDE  ${Template_SOURCE_DIR}/Source)
    set(Template_LIBRARY  ${TargetName})

endif()

subdirs(Source)

if (Template_BUILD_TEST)
    set(BUILD_GMOCK   OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

    subdirs(Test/googletest)
    subdirs(Test)
endif()
