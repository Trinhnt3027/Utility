set(UTILITY_TEST OFF CACHE BOOL "Enable Utility test" FORCE)

if (NOT ${UTILITY_TEST})
	return()
endif()

FILE(GLOB UTILITY_TEST_SRCS *.h *.cpp)

add_executable(UtilityTest ${UTILITY_TEST_SRCS})

#target_include_directories(UtilityTest  PUBLIC ${CMAKE_INSTALL_PREFIX}/include/Utility)

find_library(UtilityLib NAMES Utility)

if (NOT (${UtilityLib} STREQUAL "${UtilityLib}-NOTFOUND"))
    target_link_libraries(UtilityTest ${UtilityLib})
endif()
