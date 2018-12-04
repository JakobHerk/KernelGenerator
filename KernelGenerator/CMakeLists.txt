cmake_minimum_required(VERSION 3.5)

find_package(Boost 1.65.1)


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

target_link_libraries(${PROJECT_NAME}
  ${Boost_LIBRARIES}
  boost_system
  rt
  pthread
)