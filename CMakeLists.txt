cmake_minimum_required(VERSION 3.17)
project(p1)

set(CMAKE_CXX_STANDARD 14)

file( GLOB APP_SOURCES *.cpp )
foreach( testsourcefile ${APP_SOURCES} )
    get_filename_component(testname ${testsourcefile} NAME_WLE)
    message(STATUS "${testname} ${testsourcefile}")
    add_executable( ${testname} ${testsourcefile})
endforeach( testsourcefile ${APP_SOURCES} )