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
include_directories(common)
include_directories(core)
include_directories(mnrm)
include_directories(util)
include_directories(util/experimental)

add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(mnrm)
add_subdirectory(util)
add_subdirectory(program)
add_subdirectory(program-maxart)

#############################################################################
