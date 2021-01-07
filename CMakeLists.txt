cmake_minimum_required(VERSION 3.0.0)
project(ImgStacker VERSION 0.1.0)

cmake_policy(SET CMP0079 NEW)

add_subdirectory(scr)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(ExternalProject)

if(WIN32)
  set(BIN_OR_LIB "bin")
else()
  set(BIN_OR_LIB "lib")
endif()

message(STATUS "Subproject: zlib...")
project(zlib-download NONE)

if(WIN32)
  set(ZLIB_LIB_NAME "zlib")
else()
  set(ZLIB_LIB_NAME "z")
endif()


ExternalProject_Add(zlib_project
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG v1.2.11
    SOURCE_DIR "${CMAKE_BINARY_DIR}/zlib-src"
	BINARY_DIR "${CMAKE_BINARY_DIR}/zlib-build"
    INSTALL_DIR "${CMAKE_BINARY_DIR}/zlib-install"
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> <SOURCE_DIR>
)

add_library(zlib SHARED IMPORTED)
set_target_properties(zlib PROPERTIES
    IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/zlib-install/${BIN_OR_LIB}/${CMAKE_SHARED_LIBRARY_PREFIX}${ZLIB_LIB_NAME}${CMAKE_DEBUG_POSTFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}"
    IMPORTED_IMPLIB "${CMAKE_BINARY_DIR}/zlib-install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${ZLIB_LIB_NAME}${CMAKE_DEBUG_POSTFIX}${CMAKE_STATIC_LIBRARY_SUFFIX}"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_BINARY_DIR}/zlib-install/include"
)
add_dependencies(ImgStacker zlib_project)
target_include_directories(ImgStacker PRIVATE "${CMAKE_BINARY_DIR}/zlib-install/include")
target_link_libraries(ImgStacker zlib)
message(STATUS "Subproject: zlib...DONE")


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
set_target_properties(tiff PROPERTIES
    IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/libtiff-install/${BIN_OR_LIB}/${CMAKE_SHARED_LIBRARY_PREFIX}tiff${CMAKE_DEBUG_POSTFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}"
    IMPORTED_IMPLIB "${CMAKE_BINARY_DIR}/libtiff-install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}tiff${CMAKE_DEBUG_POSTFIX}${CMAKE_STATIC_LIBRARY_SUFFIX}"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_BINARY_DIR}/libtiff-install/include"
)
add_dependencies(ImgStacker libtiff_project)
target_include_directories(ImgStacker PRIVATE "${CMAKE_BINARY_DIR}/libtiff-install/include")
target_link_libraries(ImgStacker tiff)
message(STATUS "Subproject: libtiff...DONE")
