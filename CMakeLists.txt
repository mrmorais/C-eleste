#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)


# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(Celeste)

# Set version information in a config.h file
set(myproject_VERSION_MAJOR 1)
set(myproject_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include)
include_directories(${HEADER_PATH})

set(SOURCE_PATH ${PROJECT_SOURCE_DIR}/src)

# Define sources and executable
set(EXECUTABLE_NAME "Celeste")
set(HEADER_FILES 
	${HEADER_PATH}/game.h 
	${HEADER_PATH}/celeste.h
	${HEADER_PATH}/cell.h
	${HEADER_PATH}/container.h
	${HEADER_PATH}/iara.h
	${HEADER_PATH}/maze.h
	${HEADER_PATH}/maze_reader.h
	${HEADER_PATH}/snake.h
	${HEADER_PATH}/status_board.h
)
set(SOURCE_FILES 
	${SOURCE_PATH}/celeste.cpp
	${SOURCE_PATH}/cell.cpp
	${SOURCE_PATH}/game.cpp
	${SOURCE_PATH}/iara.cpp
	${SOURCE_PATH}/maze.cpp
	${SOURCE_PATH}/maze_reader.cpp
	${SOURCE_PATH}/snake.cpp
)
add_executable(${EXECUTABLE_NAME} src/drive.cpp ${HEADER_FILES} ${SOURCE_FILES})

target_compile_features(Celeste PRIVATE cxx_range_for)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)
