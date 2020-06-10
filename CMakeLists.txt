cmake_minimum_required(VERSION 3.0.0)
project(abcc)
enable_language(C)
set(C_STANDARD 11)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Declare main executable
file(GLOB ABCC_SOURCES src/*.c)
add_executable(abcc ${ABCC_SOURCES})

# Compiler specific
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  # Hide Console
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

# Interface libraries with main executable
target_include_directories(abcc PUBLIC src)
target_link_libraries(abcc)