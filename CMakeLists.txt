cmake_minimum_required(VERSION 3.6)
project(myBash)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp lsboost.h move.h remove.h cp.h mkdir.h help.h parse.h asking.h)
add_executable(myBash ${SOURCE_FILES})

FIND_PACKAGE( Boost COMPONENTS program_options filesystem system REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
target_link_libraries( myBash ${Boost_LIBRARIES} )

#add_executable(myLs ${LS_SOURCE_FILES})
#target_link_libraries( myBash ${Boost_LIBRARIES} )