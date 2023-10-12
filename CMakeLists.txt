#############################
# CMake - CORE Modules meta-package - root
#############################

cmake_minimum_required(VERSION 3.18.0)

project("MoHSES System")


set(VERSION_TYPE "release" CACHE STRING "version type" FORCE)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 0)
site_name(VERSION_HOST) # read hostname to VERSION_HOST
set(VERSION_HOST "${VERSION_HOST}" CACHE STRING "host of build" FORCE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)


find_package(Doxygen QUIET)
option (MOHSES_GENERATE_DOCS "Generate Doxygen based documentation files" ${Doxygen_Found})
if (MOHSES_GENERATE_DOCS)
   message(STATUS "Looking for Doxygen which is required when MOHSES_GENERATE_DOCS=ON")
   find_package(Doxygen REQUIRED)
endif()

set(OUTPUT_PREFIX ${CMAKE_BINARY_DIR}/artifacts)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/bin)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
      string(TOUPPER _${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
      set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY${OUTPUTCONFIG_UPPER} ${OUTPUT_PREFIX}/${OUTPUTCONFIG}/lib)
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY${OUTPUTCONFIG_UPPER} ${OUTPUT_PREFIX}/${OUTPUTCONFIG}/lib)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY${OUTPUTCONFIG_UPPER} ${OUTPUT_PREFIX}/${OUTPUTCONFIG}/bin)
endforeach()

include (${CMAKE_SOURCE_DIR}/cmake/common_logic.cmake)
if(NOT TARGET create_distribution_bundles)
  ###############################################################################
  # Stage Code for IDE Testing
  ###############################################################################
  create_stage()
endif()

find_package(Threads)
set(USE_FOLDERS TRUE)

set(CMAKE_MACOSX_RPATH 1)

option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" OFF)

if (MOHSES_FETCH_THIRDPARTY)

   project("MoHSES Thirdparty")
   message(STATUS "MOHSES_FETCH_THIRDPARTY=ON")
   add_subdirectory(thirdparty)
else()
   message(STATUS "MOHSES_FETCH_THIRDPARTY=OFF")
   find_package(Boost REQUIRED COMPONENTS atomic chrono date_time exception container filesystem program_options serialization system thread)

  set_target_properties(Boost::filesystem PROPERTIES
     MAP_IMPORTED_CONFIG_MINSIZEREL Release
     MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

  set_target_properties(Boost::program_options PROPERTIES
     MAP_IMPORTED_CONFIG_MINSIZEREL Release
     MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

  set_target_properties(Boost::serialization PROPERTIES
     MAP_IMPORTED_CONFIG_MINSIZEREL Release
     MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

  set_target_properties(Boost::system PROPERTIES
     MAP_IMPORTED_CONFIG_MINSIZEREL Release
     MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

  set_target_properties(Boost::thread PROPERTIES
     MAP_IMPORTED_CONFIG_MINSIZEREL Release
     MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

  set_target_properties(Boost::atomic PROPERTIES
     MAP_IMPORTED_CONFIG_MINSIZEREL Release
     MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

  set_target_properties(Boost::date_time PROPERTIES
     MAP_IMPORTED_CONFIG_MINSIZEREL Release
     MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

  set_target_properties(Boost::exception PROPERTIES
     MAP_IMPORTED_CONFIG_MINSIZEREL Release
     MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )
  
  set_target_properties(Boost::container PROPERTIES
     MAP_IMPORTED_CONFIG_MINSIZEREL Release
     MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

   if (NOT TARGET Boost::asio)
     message(STATUS "EXPORTING Boost::asio") 
     add_library(Boost::asio ALIAS Boost::headers)
   elseif(TARGET ${PACKAGE_EXPORT})
     message(STATUS "${PACKAGE_EXPORT} target exists")
   endif()
   
   if (NOT TARGET Boost::algorithm)
     message(STATUS "EXPORTING Boost::algorithm") 
     add_library(Boost::algorithm ALIAS Boost::headers)
   elseif(TARGET ${PACKAGE_EXPORT})
     message(STATUS "${PACKAGE_EXPORT} target exists")
   endif()
   
   if (NOT TARGET Boost::assign)
     message(STATUS "EXPORTING Boost::assign") 
     add_library(Boost::assign ALIAS Boost::headers)
   elseif(TARGET ${PACKAGE_EXPORT})
     message(STATUS "${PACKAGE_EXPORT} target exists")
   endif()
   
   if (NOT TARGET Boost::foreach)
     message(STATUS "EXPORTING Boost::foreach") 
     add_library(Boost::foreach ALIAS Boost::headers)
   elseif(TARGET ${PACKAGE_EXPORT})
     message(STATUS "${PACKAGE_EXPORT} target exists")
   endif()
   
   if (NOT TARGET Boost::process)
     message(STATUS "EXPORTING Boost::process") 
     add_library(Boost::process ALIAS Boost::headers)
   elseif(TARGET ${PACKAGE_EXPORT})
     message(STATUS "${PACKAGE_EXPORT} target exists")
   endif()
   
   if (NOT TARGET Boost::uuid)
     message(STATUS "EXPORTING Boost::uuid") 
     add_library(Boost::uuid ALIAS Boost::headers)
   elseif(TARGET ${PACKAGE_EXPORT})
     message(STATUS "${PACKAGE_EXPORT} target exists")
   endif()

   find_package(TinyXML2 CONFIG QUIET)
  if ( NOT TinyXML2_FOUND )
     find_package(TinyXML2 REQUIRED)
  endif()
  
  if (TINYXML2_FOUND)
     set(TINYXML2_LIBRARY tinyxml2::tinyxml2 CACHE INTERNAL "The Lirbraries of Tinyxml2" FORCE)
  endif()
  
  if (TinyXML2_FOUND AND NOT TARGET tinyxml2::tinyxml2)
     message(STATUS "EXPORTING tinyxml2::tinyxml2")
     add_library(tinyxml2::tinyxml2 UNKNOWN IMPORTED )
      
     set_target_properties(tinyxml2::tinyxml2
         PROPERTIES
         IMPORTED_LOCATION "$<$<CONFIG:Debug>:TINYXML2_LIBRARY_RELEASE>$<$<CONFIG:Release>:TINYXML2_LIBRARY_DEBUG>"
         INTERFACE_INCLUDE_DIRECTORIES
         ${TinyXML2_INCLUDE_DIR}
         ${TINYXML2_INCLUDE_DIR}
     )
     target_include_directories(tinyxml2::tinyxml2 INTERFACE $<INSTALL_INTERFACE:include> INTERFACE $<BUILD_INTERFACE:${TinyXML2_INCLUDE_DIR}> $<BUILD_INTERFACE:${TINYXML2_INCLUDE_DIR}>)
     message(STATUS "target_link_libraries(tinyxml2::tinyxml2 INTERFACE ${TINYXML2_LIBRARY} ${TinyXML2_LIBRARY})")
  elseif(TARGET tinyxml2::tinyxml2)
     message(STATUS "tinyxml2::tinyxml2 target exists")
  endif()

  find_package(foonathan_memory REQUIRED)
  find_package(SQLite3 REQUIRED)
  find_package(fastcdr REQUIRED)
  if (TARGET fastcdr AND NOT TARGET eProsima::fastcdr)
     add_library(eProsima::fastcdr ALIAS fastcdr)
  endif()

  find_package(fastrtps REQUIRED)
  
  if (TARGET fastrtps AND NOT TARGET eProsima::fastrtps)
     add_library(eProsima::fastrtps ALIAS fastrtps)
  endif()
  if (TARGET fastrtps AND NOT TARGET eProsima::fastrdds)
     add_library(eProsima::fastrdds ALIAS fastrtps)
  endif()

  find_package(Eigen3 REQUIRED)
  find_package(XercesC REQUIRED)
  find_package(CodeSynthesis REQUIRED)
  find_package(Biogears REQUIRED)

  find_package(RapidJSON REQUIRED)
  if (NOT WIN32)
     if( RAPIDJSON_INCLUDE_DIRS AND NOT TARGET rapidjson)
       add_library(rapidjson INTERFACE )
       target_include_directories(rapidjson INTERFACE  
             INTERFACE $<BUILD_INTERFACE:${RAPIDJSON_INCLUDE_DIRS}>
             $<INSTALL_INTERFACE:${RAPIDJSON_INCLUDE_DIRS}>)
     endif()
     if( TARGET rapidjson AND NOT TARGET rapidjson::headers)
       message(STATUS "Creating target rapidjson::headers")
       add_library( rapidjson::headers ALIAS rapidjson)
     endif()    

     find_package(Pistache QUIET)

     Set(FETCHCONTENT_QUIET FALSE)
     if ( NOT Pistache_FOUND )
        find_package(PkgConfig QUIET)
        if ( PkgConfig_FOUND )
           if( NOT CMAKE_FIND_ROOT_PATH )
              set(PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
           endif()

           message(STATUS " CMAKE_FIND_ROOT_PATH_MODE_LIBRARAY=${CMAKE_FIND_ROOT_PATH_MODE_LIBRARY}")
            if(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY STREQUAL ONLY OR CMAKE_FIND_ROOT_PATH_MODE_LIBRARY STREQUAL BOTH) 
              message(STATUS "Generating pkgconfig path from CMAKE_FIND_ROOT_PATH")
              foreach( dir IN LISTS CMAKE_FIND_ROOT_PATH)
               if(EXISTS "${dir}/lib/pkgconfig")
                 STRING(APPEND PKG_CONFIG_FIND_PATH ":${dir}/lib/pkgconfig")
                 STRING(APPEND PKG_CONFIG_FIND_PATH ":${dir}/lib/${CMAKE_LIBRARY_ARCHITECTURE}/pkgconfig")
               endif()
              endforeach()
           endif()
           if(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY STREQUAL NEVER OR CMAKE_FIND_ROOT_PATH_MODE_LIBRARY STREQUAL BOTH OR NOT CMAKE_FIND_ROOT_PATH_MODE_LIBRARY) 
             message(STATUS "Generating pkgconfig path from CMAKE_PREFIX_PATH")
             foreach( dir IN LISTS CMAKE_PREFIX_PATH)
               if(EXISTS "${dir}/lib/pkgconfig")
                 STRING(APPEND PKG_CONFIG_FIND_PATH ":${dir}/lib/pkgconfig")
                 STRING(APPEND PKG_CONFIG_FIND_PATH ":${dir}/lib/${CMAKE_LIBRARY_ARCHITECTURE}/pkgconfig")
               endif()
             endforeach()
           endif()

           message(STATUS "Generating pkgconfig path from CMAKE_INSTALL_PREFIX")
           foreach( dir IN LISTS CMAKE_INSTALL_PREFIX)
             if(EXISTS "${dir}/lib/pkgconfig")
               STRING(APPEND PKG_CONFIG_FIND_PATH ":${dir}/lib/pkgconfig")
               STRING(APPEND PKG_CONFIG_FIND_PATH ":${dir}/lib/${CMAKE_LIBRARY_ARCHITECTURE}/pkgconfig")
             endif()
           endforeach()

           message(STATUS "set(ENV{PKG_CONFIG_PATH} \"$ENV{PKG_CONFIG_PATH}:${PKG_CONFIG_FIND_PATH}\")")
           set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${PKG_CONFIG_FIND_PATH}")

           message(STATUS "Looking for libpistache using pkg")
           pkg_search_module(Pistache IMPORTED_TARGET GLOBAL libpistache)
           if (Pistache_FOUND)
              message(STATUS "Creating Library pistache::lib from PkgConfig::Pistache")
              add_library(pistache::lib ALIAS PkgConfig::Pistache)
           endif()
        elseif ( NOT Pistache_FOUND )
          message(STATUS "Pistache not found. Unbale to locate Pistache with out it")
        endif()
     endif()
  endif()
  message(STATUS "ADDING LIBRARIES AND MODULES")
  add_subdirectory(libraries)
  add_subdirectory(modules)
endif()

message(STATUS "")
message(STATUS "    == Final overview for ${PROJECT_NAME} ==")
message(STATUS "Version:              ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} ${VERSION_TYPE} @ ${VERSION_HOST}")
message(STATUS "Arch:                 ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMAKE_PREFIX_PATH:    ${CMAKE_PREFIX_PATH}")
if (CMAKE_FIND_ROOT_PATH)
        message(STATUS "CMAKE_FIND_ROOT_PATH: ${CMAKE_FIND_ROOT_PATH}")
endif()
message(STATUS "Install prefix:       ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Output:               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "Compiler:             ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_BUILD_TYPE:     ${CMAKE_BUILD_TYPE}")
if (MOHSES_USERNAME)
        message(STATUS "MOHSES_USERNAME: ${MOHSES_USERNAME}")
endif()
if (MOHSES_RUNTIME_DIR)
        message(STATUS "MOHSES_RUNTIME_DIR: ${MOHSES_RUNTIME_DIR}")
endif()
if (MOHSES_LOGGING_DIR)
        message(STATUS "MOHSES_LOGGING_DIR: ${MOHSES_LOGGING_DIR}")
endif()
if (MOHSES_CONFIG_DIR)
        message(STATUS "MOHSES_CONFIG_DIR: ${MOHSES_CONFIG_DIR}")
endif()
message(STATUS "")
