##################################################################################################
#
# CMake script for finding TinyXML2.
#
# Input variables:
#
# - TinyXML2_ROOT_DIR (optional): When specified, header files and libraries will be searched for in
#     ${TinyXML2_ROOT_DIR}/include
#     ${TinyXML2_ROOT_DIR}/libs
#   respectively, and the default CMake search order will be ignored. When unspecified, the default
#   CMake search order is used.
#   This variable can be specified either as a CMake or environment variable. If both are set,
#   preference is given to the CMake variable.
#   Use this variable for finding packages installed in a nonstandard location, or for enforcing
#   that one of multiple package installations is picked up.
#
#
# Cache variables (not intended to be used in CMakeLists.txt files)
#
# - TinyXML2_INCLUDE_DIR: Absolute path to package headers.
# - TinyXML2_LIBRARY: Absolute path to library.
#
#
# Output variables:
#
# - TinyXML2_FOUND: Boolean that indicates if the package was found
# - TinyXML2_INCLUDE_DIRS: Paths to the necessary header files
# - TinyXML2_LIBRARIES: Package libraries
#
#
# Example usage:
#
#  find_package(TinyXML2)
#  if(NOT TinyXML2_FOUND)
#    # Error handling
#  endif()
#  ...
#  include_directories(${TinyXML2_INCLUDE_DIRS} ...)
#  ...
#  target_link_libraries(my_target ${TinyXML2_LIBRARIES})
#
##################################################################################################

# Get package location hint from environment variable (if any)
if(NOT TinyXML2_ROOT_DIR AND DEFINED ENV{TinyXML2_ROOT_DIR})
    set(TinyXML2_ROOT_DIR "$ENV{TinyXML2_ROOT_DIR}" CACHE PATH
            "TinyXML2 base directory location (optional, used for nonstandard installation paths)")
endif()

# Search path for nonstandard package locations
if(TinyXML2_ROOT_DIR)
    set(TinyXML2_INCLUDE_PATH PATHS "${TinyXML2_ROOT_DIR}/include" NO_DEFAULT_PATH)
endif()

# Find headers and libraries

find_path(TinyXML2_INCLUDE_DIR NAMES tinyxml2.h PATH_SUFFIXES "tinyxml2" ${TinyXML2_INCLUDE_PATH})

find_library(TinyXML2_LIBRARY_RELEASE NAMES tinyxml2 )
find_library(TinyXML2_LIBRARY_DEBUG NAMES tinyxml2d tinyxml2_d tinyxml2)

mark_as_advanced(TinyXML2_INCLUDE_DIR)

# Output variables generation
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TinyXML2 DEFAULT_MSG 
                                  TinyXML2_INCLUDE_DIR 
                                  TinyXML2_LIBRARY_RELEASE 
                                  TinyXML2_LIBRARY_DEBUG
)

if(TinyXML2_FOUND)
    set(TinyXML2_INCLUDE_DIRS ${TinyXML2_INCLUDE_DIR})
    if(NOT TARGET tinyxml2::tinyxml2)
          add_library(tinyxml2::tinyxml2 INTERFACE IMPORTED GLOBAL)
          
          set_target_properties(tinyxml2::tinyxml2
          PROPERTIES
          INTERFACE_INCLUDE_DIRECTORIES
          ${TinyXML2_INCLUDE_DIR}
          )
          target_include_directories(tinyxml2::tinyxml2 INTERFACE $<INSTALL_INTERFACE:include> INTERFACE $<BUILD_INTERFACE:${TinyXML2_INCLUDE_DIR}> $<BUILD_INTERFACE:${TINYXML2_INCLUDE_DIR}>)
          target_link_libraries(tinyxml2::tinyxml2 INTERFACE $<$<CONFIG:Debug>:${TinyXML2_LIBRARY_DEBUG}> INTERFACE $<$<CONFIG:>:${TinyXML2_LIBRARY_RELEASE}> INTERFACE $<$<CONFIG:Release>:${TinyXML2_LIBRARY_RELEASE}>)
    endif()
endif()
