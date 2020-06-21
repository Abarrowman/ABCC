cmake_minimum_required(VERSION 3.1.0)
project(abcc)
enable_language(C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Compiler specific
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  # stop complaining about using fopen instead of fopen_s
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)

  # Hide Console
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

file(GLOB ABCC_LIB_SOURCES src/lib/*.c)
include_directories(abcc PUBLIC src/lib)

# Declare main executable
add_executable(abcc ${ABCC_LIB_SOURCES} src/exec/abcc.c)

# Declare test executable
add_executable(abcc-test ${ABCC_LIB_SOURCES} ${ABCC_TEST_SOURCES} src/test/abcc_test.c)