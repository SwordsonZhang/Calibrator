include(${CMAKE_CURRENT_LIST_DIR}/Common.cmake)

find_value(SDK_OpenCV_DIR SDK_OpenCV_DIR)
#message(STATUS "SDK_OpenCV_DIR: ${SDK_OpenCV_DIR}")

if(SDK_OpenCV_DIR)
  set(OpenCV_DIR ${SDK_OpenCV_DIR})
endif()

if(NOT OpenCV_DIR)
  if(DEFINED ENV{OpenCV_DIR})
    set(OpenCV_DIR $ENV{OpenCV_DIR})
  endif()
endif()

if(MSVC OR MSYS OR MINGW)
  if(NOT OpenCV_DIR)
    if(DEFINED ENV{MYNTEYE_SDK_ROOT})
      set(OpenCV_DIR $ENV{MYNTEYE_SDK_ROOT}/deps/opencv)
    else()
      if(NOT PRO_DIR)
        get_filename_component(PRO_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)
      endif()
      set(OpenCV_DIR ${PRO_DIR}/deps/opencv)
    endif()
  endif()
  if(NOT EXISTS "${OpenCV_DIR}/OpenCVConfig.cmake")
    set(OpenCV_DIR C:/opencv)
  endif()
endif()

message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")

if(OpenCV_DIR)
  if(NOT EXISTS "${OpenCV_DIR}/OpenCVConfig.cmake")
    if(EXISTS "${OpenCV_DIR}/share/OpenCV/OpenCVConfig.cmake")
      set(OpenCV_DIR "${OpenCV_DIR}/share/OpenCV")
      message(STATUS "OpenCV_DIR changed: ${OpenCV_DIR}")
    else()
      message(FATAL_ERROR "OpenCV_DIR incorrect, OpenCVConfig.cmake not found. <${OpenCV_DIR}>")
    endif()
  endif()
endif()

set(CUDA_USE_STATIC_CUDA_RUNTIME OFF CACHE BOOL "Turn off using static cuda runtime.")

find_package(OpenCV QUIET)
if(OpenCV_FOUND)
  if(OpenCV_VERSION VERSION_LESS 3.0)
    set(USE_OPENCV2 TRUE)
    add_definitions(-DUSE_OPENCV2)
  else()
    set(USE_OPENCV3 TRUE)
    add_definitions(-DUSE_OPENCV3)
  endif()
else()
  message(FATAL_ERROR "OpenCV not found. Allow set OpenCV_DIR to find it.")
endif()

message(STATUS "OpenCV_VERSION: ${OpenCV_VERSION}")
message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")

include_directories(${OpenCV_INCLUDE_DIRS})
