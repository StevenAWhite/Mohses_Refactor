cmake_minimum_required(VERSION 3.18.0)

include(GNUInstallDirs)

set(SUPERVISOR_RUNTIME_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")
set(SUPERVISOR_LOGGING_DIR "${CMAKE_INSTALL_PREFIX}/logs")
set(SUPERVISOR_CONFIG_DIR  "${CMAKE_INSTALL_PREFIX}/share/mohses/supervisor/")
set(SUPERVISOR_USERNAME    "mohses")  
if(NOT WIN32)
   if(CMAKE_INSTALL_PREFIX MATCHES "^/usr(/.*)?$")
     set(SUPERVISOR_RUNTIME_DIR "/opt/mohses/"   )
     set(SUPERVISOR_LOGGING_DIR "/var/log/mohses")
     set(SUPERVISOR_CONFIG_DIR "/etc/supervisor/conf.d/")
     set(SUPERVISOR_USERNAME    "mohses")   
    endif()
endif()

set(MOHSES_RUNTIME_DIR ${SUPERVISOR_RUNTIME_DIR} CACHE PATH "Supervisor scripts will be configured to run services in this directory. Additionally, All runtime files will be installed here" )
set(MOHSES_LOGGING_DIR ${SUPERVISOR_LOGGING_DIR} CACHE PATH "Supervisor scripts will be configured to place runtime logs in this directory" )
set(MOHSES_CONFIG_DIR ${SUPERVISOR_CONFIG_DIR} CACHE PATH "Supervisor scripts will be installed in the following directory." )
set(MOHSES_USERNAME ${SUPERVISOR_USERNAME}  CACHE STRING "Supervisor scripts will be configured, so that services run under this username" )

set(_CMAKE_FOLDER ${CMAKE_FOLDER})
set(CMAKE_FOLDER Mohses)
add_subdirectory(module-manager)
add_subdirectory(rest-adapter)
add_subdirectory(simulation-manager)
add_subdirectory(tcp-bridge)
add_subdirectory(physiology-manager)
set(CMAKE_FOLDER ${_CMAKE_FOLDER})

if (TARGET create_distribution_bundle)
  ###############################################################################
  # Add modules to the dep list for our fixup target
  # You likely need to add on project to stage for every executable you would like
  # to stage (AKA move dep DLLs to the run folder for debugging.
  ################################################################################
 
  if(TARGET  mohses_module_manager ) 
    add_dependencies(create_distribution_bundle mohses_module_manager)
  endif( )
  if( TARGET  mohses_physiology_manager )
    add_dependencies(create_distribution_bundle mohses_physiology_manager)
  endif()
  if(TARGET mohses_rest_adapter )
    add_dependencies(create_distribution_bundle mohses_rest_adapter)
  endif()
  if(TARGET mohses_simulation_manager )
    add_dependencies(create_distribution_bundle mohses_simulation_manager)
  endif()
  if(TARGET  mohses_tcp_bridge)
    add_dependencies(create_distribution_bundle mohses_tcp_bridge)
  endif()
endif()

set(OUTPUT_PREFIX "${CMAKE_INSTALL_PREFIX}")
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
      string(TOUPPER _${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
      list(APPEND FIXUP_DEFINES " -D CMAKE_ARCHIVE_OUTPUT_DIRECTORY${OUTPUTCONFIG_UPPER}=${OUTPUT_PREFIX}}/lib")
      list(APPEND FIXUP_DEFINES " -D CMAKE_LIBRARY_OUTPUT_DIRECTORY${OUTPUTCONFIG_UPPER}=${OUTPUT_PREFIX}}/lib")
      list(APPEND FIXUP_DEFINES " -D CMAKE_RUNTIME_OUTPUT_DIRECTORY${OUTPUTCONFIG_UPPER}=${OUTPUT_PREFIX}}/bin")
endforeach()

#Add Triple Dection as needed
if ( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64"  AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
 set(triple "x86_64-linux-gnu")
elseif( CMAKE_SYSTEM_PROCESSOR STREQUAL "armv8" )
 set(triple"aarch64-linux-gnu")
endif()

string(REPLACE ";" "\;" pp "${CMAKE_PREFIX_PATH}")

if ( NOT CMAKE_CROSSCOMPILING )
install(CODE 
"
message(STATUS \"Post Install Bundle Fixing\")
execute_process(COMMAND
    ${CMAKE_COMMAND} 
    ${FIXUP_DEFINES}
    -D ROOT_PROJECT_NAME=\"Biogears\"
    -D CMAKE_INSTALL_RPATH=\"\$ORIGIN\"
    -D CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}
    -D CMAKE_SYSTEM_PROCESSOR={CMAKE_SYSTEM_PROCESSOR}
    -D PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}
    -D PLATFORM_TRIPLE=${triple}
    -D CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}
    -D CMAKE_PREFIX_PATH=${pp}
    -D CMAKE_RUNTIME_PATH=${RUNTIME_PATH}
    -D CMAKE_EXECUTABLE_SUFFIX=${CMAKE_EXECUTABLE_SUFFIX}
    -D CMAKE_ARCHIVE_OUTPUT_DIRECTORY=${OUTPUT_PREFIX}/lib
    -D CMAKE_LIBRARY_OUTPUT_DIRECTORY=${OUTPUT_PREFIX}/lib
    -D CMAKE_RUNTIME_OUTPUT_DIRECTORY=${OUTPUT_PREFIX}/bin
    -D CMAKE_INSTALL_CONFIG_NAME=$<CONFIG> 
    -P \"${CMAKE_SOURCE_DIR}/cmake/fixup_bundle.cmake\"
    VERBATIM
    )
"
)

endif()
