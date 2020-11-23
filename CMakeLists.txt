cmake_minimum_required (VERSION 3.8)

project (ArenaBoss VERSION 0.1.0 LANGUAGES CXX)

# Set application to GUI type for Win32 and MacOS
if (WIN32)
  set (GUI_TYPE WIN32)
elseif (APPLE)
  set(GUI_TYPE MACOSX_BUNDLE)
endif ()

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Cmake)

include (Platform)
include (Package)
include (Util)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory (Source)