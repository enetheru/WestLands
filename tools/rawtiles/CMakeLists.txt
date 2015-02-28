cmake_minimum_required( VERSION 2.6 )
project( rawtiles )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/" )

find_package( OpenImageIO REQUIRED )
find_package( Boost REQUIRED COMPONENTS system )

include_directories( ${OpenImageIO_INCLUDE_DIRS} )

set( LIBS ${LIBS}
    ${OPENIMAGEIO_LIBRARY} )

if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Debug CACHE STRING
        "Choose the type of build, options are None, Debug, Release, RelWithDebInfo, MinSizeRel" FORCE )
endif()

set( CMAKE_CXX_FLAGS "-Wall -std=c++11" )
add_subdirectory( src )
