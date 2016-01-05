# Name  : Findjsonr-core.cmake
# Author: Cerek Hillen
#
# Description:
#   Finding jsonr after it has been installed.

# Finding the include directory.
find_path(JSONR_INCLUDE_DIRS jsonr.h
  PATHS /usr/local/include
)

# Finding the library.
find_library(JSONR_LIBRARIES
  NAMES jsonr
  PATHS /usr/local
  PATH_SUFFIXES lib/static
                lib
)

# Making sure we have everything. 
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(lentil-core REQUIRED_VARS JSONR_INCLUDE_DIRS
                                                            JSONR_LIBRARIES)
