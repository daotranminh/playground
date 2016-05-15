cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

#set (CQELS_PROJECT cqels)
set (CQELS_PROJECT playground)

MESSAGE( STATUS "CQELS_PROJECT: " ${CQELS_PROJECT} )

project (${CQELS_PROJECT})

# define some folders
get_filename_component(PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PATH)
set(RXCPP_DIR ${PARENT_DIR}/RxCpp)
set(CQELS_DIR ${PARENT_DIR}/${CQELS_PROJECT})

MESSAGE( STATUS "RXCPP_DIR: " ${RXCPP_DIR} )
MESSAGE( STATUS "CQELS_DIR: " ${CQELS_DIR} )

MESSAGE( STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR} )
MESSAGE( STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )

include(${RXCPP_DIR}/projects/CMake/shared.cmake)

# The list of CQELS source files. Please add every new file to this list
set(CQELS_SOURCES
  ${CQELS_DIR}/src/main.cpp
)

add_executable(${CQELS_PROJECT} ${CQELS_SOURCES})

target_compile_options(${CQELS_PROJECT} PUBLIC ${RX_COMPILE_OPTIONS})
target_compile_features(${CQELS_PROJECT} PUBLIC ${RX_COMPILE_FEATURES})
target_include_directories(${CQELS_PROJECT} PUBLIC ${RX_SRC_DIR} ${RX_CATCH_DIR})
target_link_libraries(${CQELS_PROJECT} ${CMAKE_THREAD_LIBS_INIT})
