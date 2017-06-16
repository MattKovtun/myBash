cmake_minimum_required(VERSION 3.5)
project(myBash)

# FF
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp lsboost.h help.h parse.cpp parse.h help.cpp  lsboost.cpp)
add_executable(myBash ${SOURCE_FILES})

FIND_PACKAGE( Boost COMPONENTS program_options filesystem system REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
target_link_libraries( myBash ${Boost_LIBRARIES} )



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


project(cp)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES cp.cpp help.h)
add_executable(cp ${SOURCE_FILES})

FIND_PACKAGE(Boost COMPONENTS program_options filesystem system REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
target_link_libraries(cp ${Boost_LIBRARIES})



project(mv)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES move.cpp help.h)
add_executable(mv ${SOURCE_FILES})

FIND_PACKAGE(Boost COMPONENTS program_options filesystem system REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
target_link_libraries(mv ${Boost_LIBRARIES})


project(ls)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES MyLs.cpp help.h)
add_executable(ls ${SOURCE_FILES})

FIND_PACKAGE(Boost COMPONENTS program_options filesystem system REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
target_link_libraries(ls ${Boost_LIBRARIES} -lboost_regex)


project(mygrep)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES mygrep.cpp)
add_executable(mygrep ${SOURCE_FILES})

FIND_PACKAGE(Boost COMPONENTS program_options filesystem system REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
target_link_libraries(mygrep ${Boost_LIBRARIES} -lboost_regex)
