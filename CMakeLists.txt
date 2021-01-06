cmake_minimum_required(VERSION 3.0.0)
project(ImgStacker VERSION 0.1.0)

add_subdirectory(scr)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(externalproject)

message(STATUS "Subproject: Libtiff...")
project(libtiff-download NONE)

ExternalProject_Add(libtiff_project
    GIT_REPOSITORY https://gitlab.com/libtiff/libtiff.git
    GIT_TAG v4.2.0
    SOURCE_DIR "${CMAKE_BINARY_DIR}/libtiff-src"
	BINARY_DIR "${CMAKE_BINARY_DIR}/libtiff-build"
    INSTALL_DIR "${CMAKE_BINARY_DIR}/libtiff-install"
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> <SOURCE_DIR>
)

add_library(tiff SHARED IMPORTED)
set_target_properties(tiff PROPERTIES IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/libtiff-install/lib")
add_dependencies(ImgStacker libtiff_project)
target_include_directories(ImgStacker PRIVATE "${CMAKE_BINARY_DIR}/libtiff-install/include")
message(STATUS "Subproject: libtiff...DONE")
