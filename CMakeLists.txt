cmake_minimum_required(VERSION 3.10)

project(geodata)
set(VERSION 1.0.0)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 14)

# Any build type flags:
# -Wall         Turn on compiler warnings.
# -fmax-errors  Number of errors after which compilation is stopped.
# -fopenmp      Support OpenMP Shared memory multiprocessing API.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fmax-errors=10")

# Debug build type flags:
# -g            Generate debug information
# -Og           Optimize for debug builds
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")

# Release build type flags:
# -O3           Optimize code for speed.
# -DNDEBUG      Turn off asserts.
# -Werror       Make all warnings into errors.
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -Werror")

# Set the source directory as relative include path.
include_directories(${PROJECT_SOURCE_DIR}/src)

if(BUILD_UNITTEST)
  message("Build unittest executable")

  file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
  file(
    GLOB_RECURSE SOURCES_EXCLUDE
    ${PROJECT_SOURCE_DIR}/src/e2etests/*.cpp
    ${PROJECT_SOURCE_DIR}/src/app/main.cpp)

  list(REMOVE_ITEM SOURCES ${SOURCES_EXCLUDE})
  add_executable(unittest ${SOURCES})
  set_target_properties(
    unittest
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_SOURCE_DIR}/build)

elseif(BUILD_E2E)
  message("Build geodata library")

  file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
  file(
    GLOB_RECURSE SOURCES_EXCLUDE
    ${PROJECT_SOURCE_DIR}/src/unittests/*.cpp
    ${PROJECT_SOURCE_DIR}/src/e2etests/*.cpp)

  list(REMOVE_ITEM SOURCES ${SOURCES_EXCLUDE})
  add_library(geodata SHARED ${SOURCES})
  set_target_properties(
    geodata
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY
    ${PROJECT_SOURCE_DIR}/build)

  message("Build e2etest executable")

  file(GLOB_RECURSE E2E_SOURCES ${PROJECT_SOURCE_DIR}/src/e2etests/*.cpp)
  add_executable(e2etest ${E2E_SOURCES})
  # ensures cross platform library detection
  find_library (geodata NAMES geodata PATHS ${PROJECT_SOURCE_DIR})
  target_link_libraries(e2etest geodata)

  set_target_properties(
    e2etest
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_SOURCE_DIR}/build)

else()
  message("Build geodata executable")

  file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
  file(
    GLOB_RECURSE SOURCES_EXCLUDE
    ${PROJECT_SOURCE_DIR}/src/unittests/*.cpp
    ${PROJECT_SOURCE_DIR}/src/e2etests/*.cpp)

  list(REMOVE_ITEM SOURCES ${SOURCES_EXCLUDE})
  add_executable(geodata ${SOURCES})
  set_target_properties(
    geodata
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_SOURCE_DIR}/build)

endif(BUILD_UNITTEST)
