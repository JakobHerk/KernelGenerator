cmake_minimum_required(VERSION 3.5)
set(BOOST_INCLUDEDIR /usr/include)
find_package(Boost 1.58.0)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

# Find source files
FILE(GLOB SOURCES src/*.cpp)
FILE(GLOB_RECURSE INC_ALL "incl/*.h")

# Include header files
include_directories(incl)

project(KernelGenerator)
# Create an executable
add_executable (${PROJECT_NAME} ${SOURCES} ${INC_ALL})


INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

target_link_libraries(${PROJECT_NAME}
  ${Boost_LIBRARIES}
  boost_system
  boost_filesystem
  boost_program_options
  rt
  pthread
)
