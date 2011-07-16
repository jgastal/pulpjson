# Locate PulpJSON library
# This module defines
# PULPJSON_LIBRARY, the name of the library to link against
# PULPJSON_FOUND, if false, do not try to link to PulpJSON
# PULPJSON_INCLUDE_DIR, where to find Parser.h and Value.h
#
#
# Created by Jonas M. Gastal.

#=============================================================================
# Copyright 2011 Jonas M. Gastal
#
# Distributed under the OSI-approved BSD License (the "License");
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================

FIND_PATH(PULPJSON_INCLUDE_DIR Parser.h Value.h
  HINTS
  $ENV{SDLDIR}
  PATH_SUFFIXES include/PulpJSON include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/
  /usr/include/
  /opt/local/include
  /opt/include
)
#MESSAGE("PULPJSON_INCLUDE_DIR is ${PULPJSON_INCLUDE_DIR}")

FIND_LIBRARY(PULPJSON_LIBRARY_TMP
  NAMES PulpJSON
  PATH_SUFFIXES lib64 lib
  PATHS
  /usr/local
  /usr
  /opt/local
  /opt
)

#MESSAGE("PULPJSON_LIBRARY_TMP is ${PULPJSON_LIBRARY_TMP}")

SET(PULPJSON_FOUND "NO")
IF(PULPJSON_LIBRARY_TMP)
  SET(PULPJSON_FOUND "YES")

  # Set the final string here so the GUI reflects the final state.
  SET(PULPJSON_LIBRARY ${PULPJSON_LIBRARY_TMP} CACHE STRING "Where the PulpJSON Library can be found")
  # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
  SET(PULPJSON_LIBRARY_TMP "${PULPJSON_LIBRARY_TMP}" CACHE INTERNAL "")

  SET(PULPJSON_FOUND "YES")
ENDIF(PULPJSON_LIBRARY_TMP)

#MESSAGE("PULPJSON_LIBRARY is ${PULPJSON_LIBRARY}")

