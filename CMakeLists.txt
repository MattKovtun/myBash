cmake_minimum_required(VERSION 3.6)
project(myBash)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp lsboost.h move.h cp.h help.h parse.h TODO.h MyLs.h)
add_executable(myBash ${SOURCE_FILES})

FIND_PACKAGE( Boost COMPONENTS program_options filesystem system REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
target_link_libraries( myBash ${Boost_LIBRARIES} -lboost_regex)



project(mkdir)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES mkdir.cpp help.h)
add_executable(mkdir ${SOURCE_FILES})

FIND_PACKAGE(Boost COMPONENTS program_options filesystem system REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
target_link_libraries(mkdir ${Boost_LIBRARIES} -lboost_regex)


project(rm)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES remove.cpp help.h)
add_executable(rm ${SOURCE_FILES})

FIND_PACKAGE(Boost COMPONENTS program_options filesystem system REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
target_link_libraries(rm ${Boost_LIBRARIES})



