#############################
# CMake Standard Library root/
#############################

cmake_minimum_required (VERSION 3.5.1)
cmake_policy(SET CMP0095 NEW)
cmake_policy(SET CMP0087 NEW)

project ("Mohses")
set(VERSION_TYPE "beta" CACHE STRING "version type" FORCE)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 0)

include(CMakePrintHelpers)

option(GENERATE_DOC "Run Doxygen to generate docs" OFF)

find_package(Boost REQUIRED)

function(install_with_directory)
    set(optionsArgs "")
    set(oneValueArgs "DESTINATION")
    set(multiValueArgs "FILES")
    cmake_parse_arguments(CAS "${optionsArgs}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    foreach(FILE ${CAS_FILES})
        get_filename_component(DIR ${FILE} DIRECTORY)
        INSTALL(FILES ${FILE} DESTINATION ${CAS_DESTINATION}/${DIR})
    endforeach()
endfunction(install_with_directory)

if (DEFINED ENV{FASTRTPS_HOME})
    list(APPEND CMAKE_PREFIX_PATH $ENV{FASTRTPS_HOME})
endif ()

if (DEFINED ENV{FASTRTPSHOME})
    list(APPEND CMAKE_PREFIX_PATH $ENV{FASTRTPSHOME})
endif ()

find_package(Boost REQUIRED COMPONENTS serialization)
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)
find_package(TinyXML2 REQUIRED)

if (COMMAND FastRTPS_IDLGEN)
    add_custom_target(generate_from_idl_standard 
             COMMAND ${FASTRTP_GEN_EXECUTABLE} 
                     -replace -d ${PROJECT_SOURCE_DIR}/src${PROJECT_SOURCE_DIR}/IDL/AMM_Standard.idl)
    add_custom_target(generate_from_idl_extended 
             COMMAND ${FASTRTP_GEN_EXECUTABLE} 
                     -replace -d ${PROJECT_SOURCE_DIR}/src${PROJECT_SOURCE_DIR}/IDL/AMM_Extended.idl)
endif()

file(GLOB_RECURSE PLOG_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/plog/*.h")
file(GLOB_RECURSE MOHSES_NET_IDL_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE MOHSES_NET_IDL_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx")
file(GLOB_RECURSE MOHSES_NET_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/mohses/*.h")
file(GLOB_RECURSE MOHSES_NET_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(MOHSES_NET_CPP ${MOHSES_NET_IDL_SOURCES} ${MOHSES_NET_SOURCES})
set(MOHSES_NET_H   ${MOHSES_NET_IDL_HEADERS} ${MOHSES_NET_HEADERS} ${PLOG_HEADERS} ) 



add_library("net" SHARED ${MOHSES_NET_CPP} ${MOHSES_NET_H})
set_target_properties(net PROPERTIES
          FOLDER "${CMAKE_FOLDER}/libraries"
          INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "" #include/plog" "src/idl"
          INSTALL_RPATH "\${ORIGIN}:\${ORIGIN}/../lib:\${ORIGIN}/lib"
)
add_library(mohses::net ALIAS net)

message(STATUS "Loading Mohses::Net")

target_link_libraries(
   net
        PUBLIC fastrtps
        PUBLIC fastcdr
        $<TARGET_NAME_IF_EXISTS:Boost::dynamic_linking>
        $<TARGET_NAME_IF_EXISTS:Boost::disable_autolinking>
        PUBLIC Boost::algorithm
        PUBLIC Boost::serialization
)

target_include_directories (net PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/idl>
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>
)

install(TARGETS net
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION "lib"
        PUBLIC_HEADER DESTINATION "include/amm"
        )
install(EXPORT ${PROJECT_NAME}
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION lib/cmake/${PROJECT_NAME}
       )
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" 
        DESTINATION "include"
        FILES_MATCHING
        PATTERN "*.h"
)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/idl/" 
        DESTINATION "include/mohses"
        FILES_MATCHING
        PATTERN "*.h"
)



include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_SOURCE_DIR}/cmake/ExportConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.cmake"
  INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )


if(MOHSES_GENERATE_DOC)
    add_subdirectory(doc)
endif(MOHSES_GENERATE_DOC)

include(Packing)
