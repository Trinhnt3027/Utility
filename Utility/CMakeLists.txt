FILE(GLOB UTILITY_COMMON_SRCS include/*.h)
FILE(GLOB UTILITY_TIMEHELPER_SRCS include/TimeHelper/*.h src/TimeHelper/*.cpp)
FILE(GLOB UTILITY_LOGGER_SRCS include/Logger/*.h src/Logger/*.cpp)

################################################################
set(UTILITY_COMBINED_SRCS ${UTILITY_TIMEHELPER_SRCS}
                          ${UTILITY_COMMON_SRCS}
                          ${UTILITY_LOGGER_SRCS})

################################################################
add_library(${PROJECT_NAME} SHARED ${UTILITY_COMBINED_SRCS})
target_compile_definitions(${PROJECT_NAME} PUBLIC -DUTILITY_LIBRARY_EXPORT)
target_compile_definitions(${PROJECT_NAME} PUBLIC -DBOOST_ALL_DYN_LINK)

################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
																									
################################################################
target_include_directories(${PROJECT_NAME}  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME}  PUBLIC ${Boost_INCLUDE_DIRS})

################################################################
target_link_libraries(${PROJECT_NAME} /usr/lib/libboost_filesystem.so)

################################################################
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME} )
