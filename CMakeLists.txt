cmake_minimum_required(VERSION 3.7.0)
project (calculator)

set (CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_BUILD_TYPE Debug)

add_executable (calculator "")
target_link_libraries (calculator PUBLIC sat)

target_sources (calculator
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src/application.c
  ${CMAKE_CURRENT_LIST_DIR}/src/common.c
  ${CMAKE_CURRENT_LIST_DIR}/src/handlers/health.c
  ${CMAKE_CURRENT_LIST_DIR}/src/handlers/calculate.c
  ${CMAKE_CURRENT_LIST_DIR}/src/handlers/report.c
  ${CMAKE_CURRENT_LIST_DIR}/src/operation.c
  ${CMAKE_CURRENT_LIST_DIR}/src/operation_request.c
  ${CMAKE_CURRENT_LIST_DIR}/src/operation_response.c
  ${CMAKE_CURRENT_LIST_DIR}/src/file_repository.c
  ${CMAKE_CURRENT_LIST_DIR}/src/mysql_repository.c
  ${CMAKE_CURRENT_LIST_DIR}/src/interval.c
  ${CMAKE_CURRENT_LIST_DIR}/src/report_request.c
  ${CMAKE_CURRENT_LIST_DIR}/src/main.c
)

target_include_directories (calculator
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)

install (TARGETS calculator DESTINATION bin)