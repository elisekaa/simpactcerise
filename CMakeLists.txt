#############################################################################
#  This file is part of the Stride software.
#  It is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or any
#  later version.
#  The software is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  You should have received a copy of the GNU General Public License,
#  along with the software. If not, see <http://www.gnu.org/licenses/>.
#  see http://www.gnu.org/licenses/.
#
#  Copyright 2018, Kuylen E et. al.
#############################################################################
#
#  CMake config.
#
#############################################################################
cmake_minimum_required(VERSION 3.5)
include(CMakeConfig.cmake)
include(CMakeLocal.cmake OPTIONAL)

#============================================================================
# Configuration for CMake, for build & install.
#============================================================================
project(simpactcerise)
set(VERSION 0.21.0)

#============================================================================
# Configuration for Git.
#============================================================================
find_package(Git)
if(GIT_FOUND)
    GIT_WC_INFO(${CMAKE_SOURCE_DIR} SIMPACT)
else()
    # This is done to eliminate blank output of undefined CMake variables.
    set(GIT_FOUND FALSE)
    set(SIMPACT_WC_REVISION_HASH       "0000-0000-000")
    set(SIMPACT_WC_LAST_CHANGED_DATE   "0000 0000 0000")
endif()

#============================================================================
# Configuration for CPP.
#============================================================================
include(CMakeCPP.cmake)

#============================================================================
# Add subdirs
#============================================================================
add_subdirectory(main)

#============================================================================
# Overview report:
#============================================================================
include(CMakeReport.cmake)

#############################################################################
