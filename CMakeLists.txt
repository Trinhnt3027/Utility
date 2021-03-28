cmake_minimum_required(VERSION 3.12)

#Project information
project("Utility" VERSION 1.0 DESCRIPTION "Lib common utility" LANGUAGES CXX)

include(Helper/CMakeLists.txt)

if (${Boost_FOUND})
    add_subdirectory(Utility)
    add_subdirectory(test)
endif()
