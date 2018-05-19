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

#============================================================================
# Add subdirs
#============================================================================
include_directories(program)
include_directories(lib/common)
include_directories(lib/core)
include_directories(lib/mnrm)
include_directories(lib/util)
include_directories(lib/util/experimental)

add_subdirectory(lib/common)
add_subdirectory(lib/core)
add_subdirectory(lib/mnrm)
add_subdirectory(lib/util)
add_subdirectory(program)
add_subdirectory(program-maxart)

#############################################################################
