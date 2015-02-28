configure_file( config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

add_executable( rawtiles main.cpp )
target_link_libraries( rawtiles ${LIBS} )
