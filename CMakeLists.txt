cmake_minimum_required (VERSION 3.0.2) 

include (GNUInstallDirs)
include (FindPkgConfig)
 
set (PROJECT modem-info)
set (VERSION 1.0.0)

if (NOT DEFINED CMAKE_INSTALL_PREFIX)
	set(CMAKE_INSTALL_PREFIX "/usr")
endif ()
 
project (${PROJECT} C)

file (GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*.c")
file (GLOB_RECURSE HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "src/*.h")

pkg_search_module (LIBXML2 REQUIRED libxml-2.0)

FIND_PACKAGE(CURL)
#pkg_search_module (CURL REQUIRED curl)

set (LIBRARIES
	${LIBXML2_LIBRARIES}
	${CURL_LIBRARIES})


set (INCLUDES
	${LIBXML2_INCLUDE_DIRS}
	${CURL_INCLUDE_DIRS})


#BUILD
	
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

include_directories (${INCLUDES})
add_executable (${PROJECT} ${HEADERS} ${SOURCES})
target_link_libraries (${PROJECT} ${LIBRARIES})


#INSTALL

install (TARGETS ${PROJECT} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

