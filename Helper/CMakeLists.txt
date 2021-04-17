#Build type: Debug/ Release
set(CMAKE_BUILD_TYPE Debug)

#Install directory
#IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
#  SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/../install CACHE PATH "Intall directory" FORCE)
#ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

#Find boost library
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

if (${WIN32})
    set(BOOST_ROOT "D:/libC++/boost_1_74_0" CACHE PATH "")
    set(BOOST_INCLUDEDIR "D:/libC++/boost_1_74_0" CACHE PATH "")
    set(BOOST_LIBRARYDIR "D:/libC++/boost_1_74_0/lib64-msvc-14.1" CACHE PATH "")
endif()

find_package(Boost COMPONENTS filesystem REQUIRED)
