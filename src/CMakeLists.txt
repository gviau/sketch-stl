cmake_minimum_required (VERSION 2.8)

project (sketch-stl)

set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib/")
set(SRC_PATH "${CMAKE_SOURCE_DIR}/src/")
set(HEADER_PATH "${CMAKE_SOURCE_DIR}/include/")

set (SRC
	${SRC_PATH}/sketch_string.cpp
)

set (HEADER
	${HEADER_PATH}/sketch_iterator.h
	${HEADER_PATH}/sketch_string.h
	${HEADER_PATH}/sketch_vector.h
)
source_group("Source Files" FILES ${SRC})
source_group("Header Files" FILES ${HEADER})

include_directories(../include/)

add_library(
    sketch-stl
    STATIC
    ${SRC}
    ${HEADER}
)

target_link_libraries(
    sketch-stl
)
