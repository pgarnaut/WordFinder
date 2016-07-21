
project(WordFinder)

MESSAGE(STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR})
MESSAGE(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE(STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR})

set(STANDALONE_SOURCES 
    WordFinder.cpp
    Combinations.cpp
    cli.cpp)



#include_directories(${CMAKE_CURRENT_SOURCE_DIR}) # needed?


# create a .so ...
#add_library(mylib SHARED ${STANDALONE_SOURCES})

# link with a .so
# target_link_libraries(myapp ${CMAKE_CURRENT_SOURCE_DIR}/somelib.so)


# link with a .so another way..
# find_library(${CMAKE_CURRENT_SOURCE_DIR}/somedir somelib)
# target_link_libraries(myapp somelib)


# c defines
add_definitions(-DLINUX)

# TODO: put a switch around these for os x vs linux
set(SUPPRESSED_WARNINGS "-Wno-deprecated-declarations -Wno-unused-function -Wno-unused-variable -Wno-unused-value -Wno-unused-but-set-variable")
set(CMAKE_C_FLAGS "-g -o0  -Wall ${SUPPRESSED_WARNINGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")


add_executable(wf-cli ${STANDALONE_SOURCES})
