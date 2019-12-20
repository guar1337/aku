cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Eloss Fortran CXX)

###################################################
#############           ROOT          #############
###################################################
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})
include(${ROOT_USE_FILE})

###################################################
#############           //ROOT        #############
###################################################

find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIR} ${CMAKE_SOURCE_DIR} )

set(SOURCE_FILES ELOSS.f90
                 ELC.cpp
                 AELC.cpp)                

add_library(Eloss SHARED ${SOURCE_FILES} )
target_link_libraries(Eloss GSL::gsl GSL::gslcblas ${ROOT_LIBRARIES})
