cmake_minimum_required(VERSION 3.5)
project(camera_calib)

# include(): load and run cmake code from the file given
include(${PROJECT_SOURCE_DIR}/cmake/Common.cmake)  

# flags
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -03")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -03")

include(${PROJECT_SOURCE_DIR}/cmake/DetectCXX11.cmake)

# include files with suffix .h in directory /mynteye_include
include_directories(${PROJECT_SOURCE_DIR}/mynteye_include)

# include file Calibrator.h
include_directories(${PROJECT_SOURCE_DIR}/include)


# link files with suffix .so in directory /mynteye_lib
set(SDK_LIBS "${PROJECT_SOURCE_DIR}/mynteye_lib")
# message(STATUS "SDK_LIBS: ${SDK_LIBS}")

# set libmynteye.so to be 
set(SDK_LIBS_CORE ${CMAKE_SHARED_LIBRARY_PREFIX}mynteye_core${CMAKE_SHARED_LIBRARY_SUFFIX})
# message(STATUS "SDK_LIBS_CORE: ${SDK_LIBS_CORE}")

# output, storge files with suffix .a/.so into lib, and files with suffix .o into bin
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
	string(TOUPPER ${CONFIG} CONFIG)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

# required OpenCV libraries
include(${PROJECT_SOURCE_DIR}/cmake/DetectOpenCV.cmake)

set(SOURCES src/mynteye_camera_calib.cpp include/Calibrator.cpp)
add_executable(mynteye_camera_calib ${SOURCES})
target_link_libraries(mynteye_camera_calib ${OpenCV_LIBS} ${SDK_LIBS}/${SDK_LIBS_CORE})
