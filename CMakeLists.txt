cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set (PLAYGROUND playground)

project (${PLAYGROUND})

# define some folders
get_filename_component(PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PATH)
set(PLAYGROUND_DIR ${PARENT_DIR}/${PLAYGROUND})

MESSAGE( STATUS "PROJECT_DIR: " ${PLAYGROUND_DIR} )

MESSAGE( STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR} )
MESSAGE( STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )

# The list of CQELS source files. Please add every new file to this list
set(PLAYGROUND_SOURCES
  ${PLAYGROUND_DIR}/src/main.cpp
)

add_executable(${PLAYGROUND} ${PLAYGROUND_SOURCES})

target_link_libraries(${PLAYGROUND} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PLAYGROUND} ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_REGEX_LIBRARY} )

find_package( Boost REQUIRED COMPONENTS program_options regex )
include_directories( ${Boost_INCLUDE_DIRS} )
