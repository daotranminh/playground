cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

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


set(BIND_SOURCES
  ${PLAYGROUND_DIR}/src/tryboost/bind.cpp
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


set(ASIO_SOURCES
  ${PLAYGROUND_DIR}/src/tryboost/asio.cpp
)


set(MULTI_INDEX_SOURCES
  ${PLAYGROUND_DIR}/src/tryboost/multi_index.cpp
)


set(SYNC_ECHO_CLIENT_SOURCES
  ${PLAYGROUND_DIR}/src/tryboost/SyncEchoClient.cpp
)


set(SYNC_ECHO_SERVER_SOURCES
  ${PLAYGROUND_DIR}/src/tryboost/SyncEchoServer.cpp
)


set(ASYNC_ECHO_CLIENT_SOURCES
  ${PLAYGROUND_DIR}/src/tryboost/AsyncEchoClient.cpp
)


set(ASYNC_ECHO_SERVER_SOURCES
  ${PLAYGROUND_DIR}/src/tryboost/AsyncEchoServer.cpp
)



set(TEMPLATE_SOURCES
  ${PLAYGROUND_DIR}/src/trytemplate/main.cpp
)


find_package( Boost REQUIRED COMPONENTS program_options regex thread system)
include_directories( ${Boost_INCLUDE_DIRS} )

MESSAGE( STATUS "BOOST_DIR: " ${Boost_INCLUDE_DIRS} )

add_executable(${PLAYGROUND} ${PLAYGROUND_SOURCES})
add_executable(array ${ARRAY_SOURCES})
add_executable(bind ${BIND_SOURCES})
add_executable(program_options ${PROGRAM_OPTIONS_SOURCES})
add_executable(optional ${OPTIONAL_SOURCES})
add_executable(variant ${VARIANT_SOURCES})
add_executable(trytemplate ${TEMPLATE_SOURCES})
add_executable(asio ${ASIO_SOURCES})
add_executable(multi_index ${MULTI_INDEX_SOURCES})

add_executable(sync_echo_client ${SYNC_ECHO_CLIENT_SOURCES})
add_executable(sync_echo_server ${SYNC_ECHO_SERVER_SOURCES})
add_executable(async_echo_client ${ASYNC_ECHO_CLIENT_SOURCES})
add_executable(async_echo_server ${ASYNC_ECHO_SERVER_SOURCES})


target_link_libraries(${PLAYGROUND} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(program_options ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_REGEX_LIBRARY})
target_link_libraries(asio ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})
target_link_libraries(sync_echo_client ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})
target_link_libraries(sync_echo_server ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})
target_link_libraries(async_echo_client ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})
target_link_libraries(async_echo_server ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})

