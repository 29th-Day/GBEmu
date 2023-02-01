cmake_minimum_required(VERSION 3.10.0)
project(GBEmu VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE SRC_FILES lib/*.c)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/emu.h
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
