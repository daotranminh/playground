cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set (PLAYGROUND playground)

project (${PLAYGROUND})

# define some folders
get_filename_component(PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PATH)
set(PLAYGROUND_DIR ${PARENT_DIR}/${PLAYGROUND})

MESSAGE( STATUS "PROJECT_DIR: " ${PLAYGROUND_DIR} )

MESSAGE( STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR} )
MESSAGE( STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )

set(Boost_USE_PROGRAM_OPTIONS ON) 

# The list of source files. Please add every new file to this list
set(PLAYGROUND_SOURCES
  ${PLAYGROUND_DIR}/src/main.cpp
)

set(ARRAY_SOURCES
  ${PLAYGROUND_DIR}/src/tryboost/array.cpp
)

set(PROGRAM_OPTIONS_SOURCES
  ${PLAYGROUND_DIR}/src/tryboost/program_options.cpp
)

set(OPTIONAL_SOURCES
  ${PLAYGROUND_DIR}/src/tryboost/optional.cpp
)

set(VARIANT_SOURCES
  ${PLAYGROUND_DIR}/src/tryboost/variant.cpp
)

find_package( Boost REQUIRED COMPONENTS program_options regex )
include_directories( ${Boost_INCLUDE_DIRS} )

add_executable(${PLAYGROUND} ${PLAYGROUND_SOURCES})
add_executable(array ${ARRAY_SOURCES})
add_executable(program_options ${PROGRAM_OPTIONS_SOURCES})
add_executable(optional ${OPTIONAL_SOURCES})
add_executable(variant ${VARIANT_SOURCES})

target_link_libraries(${PLAYGROUND} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(program_options ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_REGEX_LIBRARY} )



