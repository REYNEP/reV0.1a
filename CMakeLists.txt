# ***** BEGIN GPL LICENSE BLOCK *****
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# The Original Code is Copyright (C) 2021, REYNEP
#
# ***** END GPL LICENSE BLOCK *****
#
#   TODO: use find_library(REQUIRED) after some time.... as it was introduced in 3.18. and the error msg can't be customized
#   TODO: use find_library(NO_CACHE) after some time.... as it was introduced in 3.21
#

cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(re VERSION 0.1)

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "" FORCE)   #Blender Stuffs....
  set(   LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE INTERNAL "" FORCE)   #Blender Stuffs....

  list(APPEND   CMAKE_MODULE_PATH   ${CMAKE_SOURCE_DIR}/buildFiles)             # for amGHOST
  include(buildFiles/build_help.cmake)

  option(_PILOT_INSTALL_ "[only for UNIX]    install inside $ENV{HOME}/.cargo/bin     [why PILOT? it means 'EXPERIMENTAL']" ON)


# --------------------
set(SRC
  "coDe/wallowsV2.cpp"
  #coDe/Gavi/T1.cpp
  #coDe/dayglow.cpp
)

set(INC
  ./
  ./amGHOST/
  ./coDe/
  ./amVK/

  #Shaders
  ./agents
)


# subDirectories -----
add_subdirectory(amGHOST)
add_subdirectory(amVK)


# re.exe -------------
add_executable(re ${SRC})
target_include_directories(re PUBLIC ${INC})
target_link_libraries(re lib-amGHOST lib-amVK)

#target_compile_options(re PUBLIC "/P")   # -E for GCC
#target_precompile_headers(re PUBLIC pch.h)
#TODO Wuffs with MSVC+X64 needs /arch:AVX for best performance


# --------------------
install(TARGETS re
  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

if (_PILOT_INSTALL_ AND UNIX)
  install(TARGETS re
  DESTINATION $ENV{HOME}/.cargo/bin)
endif()
