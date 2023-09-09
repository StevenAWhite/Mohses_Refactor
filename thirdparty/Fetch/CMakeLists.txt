#  Meta CMakeLists.txt for Building Biogears and all of its dependencies. 
#  It supports fowarding the following variables to each project
#
#  CMAKE_TOOLCHAIN_FILE      :   Which TOOLCHAIN will be used by the project
#  ANDROID_ABI        STRING :   Valid form   android-## or ##
#  ANDROID_PLATFORM   STRING :   Valid Values [armeabi-v7a,arm64-v8a, x86_64]
#  ANDROID_ARM_NEON   BOOL   :   Enables NEON for armeabi-v7a
#  CMAKE_PREFIX_PATH    FILEPATH : Should not be required as all Thirdparty projects are built by this script
#
#  CMAKE_ROOT_FIND_PATH FILEPATH : Location of Cross-compilation requirments if required I 
#
#  CMAKE_INSTALL_PREFIX FILEPATH : Where do you want all built artifacts to be stored
#  XERCES_C_transcoder : Adjust the Xerces-C Transcoder

cmake_minimum_required(VERSION 3.18)

project (BioGears_and_dependencies C CXX)

find_package(Git REQUIRED)

include(ExternalProject)

#  I want to support cross compilation in a generic way so I don't have to many if else sections
#  So, this section checks known variabels were defined to the Meta script and then 
#  creates arguments if they exist else it creates blank arguments. The end affect is that
#  only the arguments that exist are sent to ExternalProjectAdds

#
#  XSD Code Synthesis 4.0
#  I've unextracted these binaries and stored thm in a github repo to work around som
#  complications we had in the build process.  
#
#  XSD is installed in the CMAKE_INSTALL_PREFIX except when CMAKE_FIND_ROOT_PATH_MODE_PROGRAM is NEVER
#  Then it is installed in CMAKE_INSTALL_PREFIX/${CMAKE_HOST_SYSTEM_NAME}

function (sanatize_path_list path_list results)
  set(${results} "")
  foreach( path IN LISTS ${path_list})
    file(TO_CMAKE_PATH ${path} cmake_path)
    LIST(APPEND ${results} ${cmake_path})
  endforeach()
  message( STATUS "${path_list}=${${results}}")
  string(REPLACE ";" "|"  safe_${results} "${${results}}")
  set (${results} ${safe_${results}} PARENT_SCOPE)
endfunction()

if(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM STREQUAL NEVER)
  set (NATIVE_INSTALL_LOCATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_HOST_SYSTEM_NAME})
  set (CROSS_BUILD ON)
  list(APPEND CMAKE_PREFIX_PATH ${NATIVE_INSTALL_LOCATION})
else()
  set (NATIVE_INSTALL_LOCATION ${CMAKE_INSTALL_PREFIX})
  set (CROSS_BUILD OFF)
endif()


if(CMAKE_INSTALL_PREFIX)
  sanatize_path_list(CMAKE_INSTALL_PREFIX _cmake_path_list)
  set(CMAKE_INSTALL_PREFIX_ARGUEMENTS "-DCMAKE_INSTALL_PREFIX:PATH=${_cmake_path_list}")
endif()
if (CMAKE_TOOLCHAIN_FILE)
  sanatize_path_list(CMAKE_TOOLCHAIN_FILE _cmake_path_list)
  set (CMAKE_TOOLCHAIN_ARGUMENTS "-DCMAKE_TOOLCHAIN_FILE:FILEPATH=${_cmake_path_list}")
endif()
if (CMAKE_FIND_ROOT_PATH)
  sanatize_path_list(CMAKE_FIND_ROOT_PATH _safe_find_root)
  set (CMAKE_FIND_ROOT_PATH_ARGUMENTS "-DCMAKE_FIND_ROOT_PATH:PATH=${_safe_find_root}")
endif()

if (CMAKE_PREFIX_PATH)
  sanatize_path_list(CMAKE_PREFIX_PATH _safe_find_root)
  set (CMAKE_PREFIX_PATH_ARGUMENTS "-DCMAKE_PREFIX_PATH:PATH=${_safe_find_root}")
endif()
if(CMAKE_MAKE_PROGRAM)
  sanatize_path_list(CMAKE_MAKE_PROGRAM _safe_find_root)
  set(CMAKE_MAKE_PROGRAM_ARGUMENTS  "-DCMAKE_MAKE_PROGRAM:FILEPATH=${_safe_find_root}")
endif()
if(ANDROID_STL)
  sanatize_path_list(ANDROID_STL _safe_find_root)
  set(ANDROID_STL_ARGUMENTS "-DANDROID_STL:STRING=${_safe_find_root}")
endif()
if(ANDROID_CPP_FEATURES)
  sanatize_path_list(ANDROID_CPP_FEATURES _safe_find_root)
  set(ANDROID_CPP_FEATURES_ARGUMENTS "-DANDROID_CPP_FEATURES:STRING=${_safe_find_root}")
endif()
if(ANDROID_ABI)
  sanatize_path_list(ANDROID_ABI _safe_find_root)
  set(ANDROID_ABI_ARGUMENTS "-DANDROID_ABI:STRING=${_safe_find_root}")
endif()
if(ANDROID_ARM_NEON)
  sanatize_path_list(ANDROID_ARM_NEON _safe_find_root)
  set(ANDROID_ARM_NEON_ARGUMENTS "-DANDROID_ARM_NEON:BOOL=${_safe_find_root}")
endif()
if(ANDROID_PLATFORM)
  sanatize_path_list(ANDROID_PLATFORM _safe_find_root)
  set(ANDROID_PLATFORM_ARGUMENTS "-DANDROID_PLATFORM:STRING=${_safe_find_root}")
endif(ANDROID_PLATFORM)
if(XERCES_C_transcoder)
  sanatize_path_list(XERCES_C_transcoder _safe_find_root)
  set(XERCES_C_TRANSCORDER_ARGUMENTS -D transcoder:STRING=${_safe_find_root})
endif()


function(Thirdparty_build _target_name) 
cmake_parse_arguments("" "NATIVE_CODE" "GIT_REPOSITORY;GIT_TAG" "CMAKE_ARGS" ${ARGN})

set(Status_Message "\"${_target_name}\" \n")
string(APPEND Status_Message "\tExternalProject_Add\" \n")
string(APPEND Status_Message "\t\tGIT_REPOSITORY \"${_GIT_REPOSITORY}\" \n")
string(APPEND Status_Message "\t\tGIT_TAG \"${_GIT_TAG}\" \n")
string(APPEND Status_Message "\t\tCMAKE_ARGS")


set(INSTALL_DIR  "../${_target_name}")
set(BINARY_DIR   "../${_target_name}/build/")
set(SOURCE_DIR   "../${_target_name}/source/")
set(DOWNLOAD_DIR "../${_target_name}/stage/")
set(STAMP_DIR    "../${_target_name}/stamp/")
set(LOG_DIR      "../${_target_name}/logs/")

if(_NATIVE_CODE)
    if(NOT NATIVE_CODE_GENERATOR)
          string(APPEND Status_Message  " -G ${CMAKE_GENERATOR}\"")
          if(CMAKE_TOOLCHAIN_ARGUMENTS)
          endif()
          ExternalProject_Add( 
            ${_target_name}
            INSTALL_DIR  ${INSTALL_DIR} 
            BINARY_DIR   ${BINARY_DIR}
            SOURCE_DIR   ${SOURCE_DIR}
            DOWNLOAD_DIR ${DOWNLOAD_DIR}
            STAMP_DIR    ${STAMP_DIR}
            LOG_DIR      ${LOG_DIR}
            GIT_REPOSITORY "${_GIT_REPOSITORY}"
            GIT_TAG "${_GIT_TAG}"
            LIST_SEPARATOR |
            CMAKE_ARGS
                        ${_CMAKE_ARGS}
                        ${CMAKE_INSTALL_PREFIX_ARGUEMENTS}
          )
    else()
        string(STRIP ${NATIVE_CODE_GENERATOR} NATIVE_CODE_GENERATOR_ARGUMENTS)
        string(APPEND Status_Message  " -G ${NATIVE_CODE_GENERATOR_ARGUMENTS}\"")
        ExternalProject_Add( 
            ${_target_name}
            INSTALL_DIR  ${INSTALL_DIR} 
            BINARY_DIR   ${BINARY_DIR}
            SOURCE_DIR   ${SOURCE_DIR}
            DOWNLOAD_DIR ${DOWNLOAD_DIR}
            STAMP_DIR    ${STAMP_DIR}
            LOG_DIR      ${LOG_DIR}
            GIT_REPOSITORY "${_GIT_REPOSITORY}"
            GIT_TAG "${_GIT_TAG}"
            LIST_SEPARATOR |
            CMAKE_GENERATOR "${NATIVE_CODE_GENERATOR_ARGUMENTS}"
            CMAKE_ARGS  ${_CMAKE_ARGS}
                        ${CMAKE_INSTALL_PREFIX_ARGUEMENTS}
          )
    endif()
else()
  string(APPEND Status_Message " -G ${CMAKE_GENERATOR}\"")
  ExternalProject_Add(
    ${_target_name}
    INSTALL_DIR  ${INSTALL_DIR} 
    BINARY_DIR   ${BINARY_DIR}
    SOURCE_DIR   ${SOURCE_DIR}
    DOWNLOAD_DIR ${DOWNLOAD_DIR}
    STAMP_DIR    ${STAMP_DIR}
    LOG_DIR      ${LOG_DIR}
    GIT_REPOSITORY "${_GIT_REPOSITORY}"
    GIT_TAG "${_GIT_TAG}"
    LIST_SEPARATOR |
    CMAKE_ARGS  -G "${CMAKE_GENERATOR}"
          ${_CMAKE_ARGS}
          ${CMAKE_TOOLCHAIN_ARGUMENTS}
	    	  ${ANDROID_STL_ARGUMENTS}
		      ${ANDROID_CPP_FEATURES_ARGUMENTS}
          ${ANDROID_ABI_ARGUMENTS}
          ${ANDROID_ARM_NEON_ARGUMENTS}
          ${ANDROID_PLATFORM_ARGUMENTS}
          ${CMAKE_FIND_ROOT_PATH_ARGUMENTS}
          ${CMAKE_PREFIX_PATH_ARGUMENTS}
          ${CMAKE_MAKE_PROGRAM_ARGUMENTS}
          ${CMAKE_INSTALL_PREFIX_ARGUEMENTS}
    )

  if(CMAKE_TOOLCHAIN_ARGUMENTS)
   string(APPEND Status_Message   " \n\t\t\t ${CMAKE_TOOLCHAIN_ARGUMENTS}")
  endif()
  if(ANDROID_STL_ARGUMENTS)
   string(APPEND Status_Message   " \n\t\t\t ${ANDROID_STL_ARGUMENTS}")
  endif()
  if(ANDROID_CPP_FEATURES_ARGUMENTS)
    string(APPEND Status_Message   " \n\t\t\t ${ANDROID_CPP_FEATURES_ARGUMENTS}")
  endif()
  if(ANDROID_ABI_ARGUMENTS)
   string(APPEND Status_Message   " \n\t\t\t ${ANDROID_ABI_ARGUMENTS}")
  endif()
  if(ANDROID_ARM_NEON_ARGUMENTS)
    list(APPEND Status_Message   " \n\t\t\t ${ANDROID_ARM_NEON_ARGUMENTS} ")
  endif()
  if(ANDROID_PLATFORM_ARGUMENTS)
    list(APPEND Status_Message   " \n\t\t\t ${ANDROID_PLATFORM_ARGUMENTS}")
  endif()
  if(CMAKE_FIND_ROOT_PATH_ARGUMENTS)
    list(APPEND Status_Message   " \n\t\t\t ${CMAKE_FIND_ROOT_PATH_ARGUMENTS}")
  endif()
  if(CMAKE_PREFIX_PATH_ARGUMENTS)
    list(APPEND Status_Message   " \n\t\t\t ${CMAKE_PREFIX_PATH_ARGUMENTS}")
  endif()
  if(CMAKE_MAKE_PROGRAM_ARGUMENTS)
     list(APPEND Status_Message   " \n\t\t\t ${CMAKE_MAKE_PROGRAM_ARGUMENTS}")
  endif()
endif()

foreach(argument IN LISTS _CMAKE_ARGS )
  string(APPEND Status_Message " \n\t\t\t ${argument}")
endforeach()
     
if(CMAKE_INSTALL_PREFIX_ARGUEMENTS)
    list(APPEND Status_Message   " \n\t\t\t " ${CMAKE_INSTALL_PREFIX_ARGUEMENTS} "" )
endif()

message(STATUS ${Status_Message})
endfunction()

message(STATUS "")

if (NOT XSD_CMAKE_GENERATOR )
	set(XSD_CMAKE_GENERATOR ${CMAKE_GENERATOR})
endif()

find_package(OpenSSL QUIET GLOBAL)
if(NOT OpenSSL_FOUND)
  if(MSVC)
     message(STATUS "OpenSSL binaries are required for this build. Downloads are avaliable for Windows at Shining Light Productions.\n"
                    "https://slproweb.com/products/Win32OpenSSL.html . The full development installation of OpenSSL v3.1.1 140MBs.\n"
                    "Adjust CMAKE_PREFIX_PATH with the folder containing the instllation.\n")
  else()
    Thirdparty_Build(openssl
      GIT_REPOSITORY https://github.com/viaduck/openssl-cmake.git
      GIT_TAG 3.0
    )
  endif()
endif()

find_package(Boost QUIET GLOBAL)
if(NOT Boost_FOUND)
  Thirdparty_Build(boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.82.0
  )
endif()

find_package(TinyXML2 QUIET GLOBAL)
if(NOT TinyXML2_FOUND)
  Thirdparty_Build(tinyxml2
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
    GIT_TAG 8.1.0
    CMAKE_ARGS -Dtinyxml2_BUILD_TESTING:BOOL=OFF
               -DBUILD_SHARED_LIBS:BOOL=ON
  
  )
endif()

find_package(foonathan_memory QUIET GLOBAL)
if(NOT foonathan_memory_FOUND)
  Thirdparty_Build(foonathan_memory
    GIT_REPOSITORY  https://github.com/foonathan/memory.git
    GIT_TAG v0.7-3
    CMAKE_ARGS -Dfoonathan_memory_BUILD_EXAMPLES:BOOL=OFF
               -Dfoonathan_memory_BUILD_TESTS:BOOL=OFF
               -Dfoonathan_memory_BUILD_TOOLS:BOOL=ON
  )
endif()

find_package(SQLite3 QUIET GLOBAL)
if(NOT SQLite3_FOUND)
  Thirdparty_Build(SQLite3
    GIT_REPOSITORY  https://github.com/azadkuh/sqlite-amalgamation.git
    GIT_TAG master
  )
endif()

find_package(fastcrr QUIET GLOBAL)
if(NOT fastcdr_FOUND)
  Thirdparty_Build(fastcdr
    GIT_REPOSITORY  https://github.com/eProsima/Fast-CDR.git
    GIT_TAG v1.0.27
  )
endif()

find_package(fastddr QUIET GLOBAL)
if(NOT fastddr_FOUND)
  Thirdparty_Build(fastddr
    GIT_REPOSITORY  https://github.com/eProsima/Fast-DDS.git
    GIT_TAG v2.10.0
    CMAKE_ARGS -DTHIRDPARTY_Asio:BOOL=ON
  )

  if(TARGET tinyxml2) 
    ExternalProject_Add_StepDependencies(fastddr build tinyxml2)
  endif()

  if(TARGET foonathan_memory)  
    ExternalProject_Add_StepDependencies(fastddr build foonathan_memory)
  endif()

  if(TARGET openssl)
    ExternalProject_Add_StepDependencies(fastddr build openssl)
  endif()

  if(TARGET fastcdr)
   ExternalProject_Add_StepDependencies(fastddr build fastcdr)
  endif()

endif()

find_package(rapidjson QUIET GLOBAL)
if(NOT rapidjson_FOUND)
  Thirdparty_Build(rapidjson
    GIT_REPOSITORY  https://github.com/Tencent/rapidjson.git
    GIT_TAG v1.1.0
    CMAKE_ARGS -DRAPIDJSON_BUILD_DOC:BOOL=OFF
               -DRAPIDJSON_BUILD_EXAMPLES:BOOL=OFF
               -DRAPIDJSON_BUILD_TESTS:BOOL=OFF
  )
endif()

find_package(foonathan_memory QUIET GLOBAL)
if(NOT foonathan_memory_FOUND)
  Thirdparty_Build(xerces-c
    GIT_REPOSITORY https://github.com/apache/xerces-c.git
    GIT_TAG xerces-3.2.2
    CMAKE_ARGS ${XERCES_C_TRANSCORDER_ARGUMENTS}
  )
endif()

find_package(xsd QUIET GLOBAL)
if(NOT xsd_FOUND)
  Thirdparty_Build(xsd
    GIT_REPOSITORY https://github.com/StevenAWhite/CodeSynthesisXSD-Binary.git
    NATIVE_CODE
    CMAKE_ARGS    -D XSD_CROSS_INSTALL:BOOL=${CROSS_BUILD}
  )

  if(TARGET xerces-c)
    ExternalProject_Add_StepDependencies(xsd build xerces-c)
  endif()
endif()


if(ANDROID)
  # Android doesn't ship with a good transcoder for UTF
  # Characters so we need to build it

  Thirdparty_Build(icu
    GIT_REPOSITORY https://github.com/StevenAWhite/icu-cmake.git
  )
  if(TARGET icu AND TARGET xerces-c)
    ExternalProject_Add_StepDependencies(xerces-c build icu)
  endif()
endif()

find_package(Eigen3 QUIET GLOBAL)
if(NOT Eigen3_FOUND)
  Thirdparty_Build(eigen
    GIT_REPOSITORY https://gitlab.com/stevenawhite/eigen.git
    GIT_TAG 3.3.9.X
    CMAKE_ARGS 
               -DBUILD_TESTING:BOOL=OFF
               -DEIGEN_BUILD_BTL:BOOL=OFF
               -DEIGEN_HEADER_ONLY:BOOL=ON
  )
endif()

find_package(Biogears QUIET GLOBAL)
if(Biogears_FOUND)
  Thirdparty_Build(biogears
    GIT_REPOSITORY https://github.com/BioGearsEngine/core.git
    GIT_TAG  trunk
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DBiogears_NO_DEBUG_POSTIFX=ON
               -DCMAKE_DEBUG_POSTFIX=
               -DBiogears_COMMON_BUILD_STATIC=OFF
               -DBiogears_BUILD_HOWTOS:BOOL=OFF
               -DBiogears_BUILD_CIRCUIT_TESTS:BOOL=OFF
               -DBiogears_BUILD_CIRCUIT_PROFILER:BOOL=OFF
               -DBiogears_BUILD_TEST_DRIVER:BOOL=OFF
               -DBiogears_BUILD_TEST:BOOL=OFF
               -DBiogears_BUILD_WEBSITE:BOOL=OFF
               -DBiogears_BUILD_TOOLS:BOOL=ON
               -DBiogears_IO_INCLUDE_STATES:BOOL=ON
               -DBiogears_PREPARE_RUNTIME_DIR:BOOL=OFF
               -DBiogears_BREAKOUT_INSTALL:BOOL=OFF
               -DBiogears_IO_USE_SHORT_TARGET_NAMES=ON
               -DXSD_USE_SHORT_TARGET_NAMES=ON
  )
  
  if(TARGET xsd)  
    ExternalProject_Add_StepDependencies(biogears build xsd)
  endif()

  if(TARGET eigen)
    ExternalProject_Add_StepDependencies(biogears build eigen)
  endif()

endif()

find_package(zlib QUIET GLOBAL)
if(NOT zlib_FOUND)
  Thirdparty_Build(zlib
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG master
  )
endif()

######
#
# Pistache -- 
# https://github.com/pistacheio/pistache.git
#####
find_package(PkgConfig)
pkg_check_modules(Pistache QUIET IMPORTED_TARGET libpistache)

if(TARGET PkgConfig::Pistache)
  if (NOT MSVC)
    find_program (MESON_EXECUTABLE 
                  NAMES meson)
    
    if (MESON_EXECUTABLE)
    
    get_filename_component(ABSOLUTE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}" ABSOLUTE)
    
    ExternalProject_Add( 
      pistache
      INSTALL_DIR  "${CMAKE_CURRENT_BINARY_DIR}/pistache"
      BINARY_DIR   "${CMAKE_CURRENT_BINARY_DIR}/pistache/build/"
      SOURCE_DIR   "${CMAKE_CURRENT_BINARY_DIR}/pistache/source/"
      DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/pistache/stage/"
      STAMP_DIR    "${CMAKE_CURRENT_BINARY_DIR}/pistache/stamps/"
      LOG_DIR      "${CMAKE_CURRENT_BINARY_DIR}/pistache/logs/"
      GIT_REPOSITORY "https://github.com/pistacheio/pistache.git"
      GIT_TAG "master"
      LIST_SEPARATOR |
      CONFIGURE_COMMAND 
        meson setup 
        --buildtype=release
        -DPISTACHE_USE_SSL=true
        -DPISTACHE_BUILD_EXAMPLES=false
        -DPISTACHE_BUILD_TESTS=false
        -DPISTACHE_BUILD_DOCS=false
        -DPISTACHE_USE_CONTENT_ENCODING_DEFLATE=true
        --prefix=${ABSOLUTE_INSTALL_PREFIX}
        --pkg-config-path=${ABSOLUTE_INSTALL_PREFIX}
        --cmake-prefix-path=${ABSOLUTE_INSTALL_PREFIX}
        ${CMAKE_CURRENT_BINARY_DIR}/pistache/build/
        ${CMAKE_CURRENT_BINARY_DIR}/pistache/source/
      BUILD_COMMAND 
        meson compile -C ${CMAKE_CURRENT_BINARY_DIR}/pistache/build/
      INSTALL_COMMAND
        meson install -C ${CMAKE_CURRENT_BINARY_DIR}/pistache/build/
    )

    if(TARGET zlib) 
      ExternalProject_Add_StepDependencies(pistache build zlib)
    endif()
   
    if(TARGET rapidjson)
      ExternalProject_Add_StepDependencies(pistache build rapidjson)
    endif()

    message(STATUS 
       "Pistache \n"
       "\tExternalProject_Add\" \n"
       "\t\tGIT_REPOSITORY https://github.com/pistacheio/pistache.git \n"
       "\t\tGIT_TAG master \n"
       "\t\tCMAKE_ARGS\n"
       "\t\tCONFIGURE_COMMAND\n"
       "\t\t    meson setup\n"
       "\t\t    --buildtype=release\n"
       "\t\t    -DPISTACHE_USE_SSL=true\n"
       "\t\t    -DPISTACHE_BUILD_EXAMPLES=false\n"
       "\t\t    -DPISTACHE_BUILD_TESTS=false\n"
       "\t\t    -DPISTACHE_BUILD_DOCS=false\n"
       "\t\t    -DPISTACHE_USE_CONTENT_ENCODING_DEFLATE=true\n"
       "\t\t    --prefix=\"${ABSOLUTE_INSTALL_PREFIX}\"\n"
       "\t\t    ${CMAKE_CURRENT_BINARY_DIR}/pistache/build/\n"
       "\t\t    ${CMAKE_CURRENT_BINARY_DIR}/pistache/source/\n"
       "\t\t  BUILD_COMMAND\n"
       "\t\t    meson compile -C ${CMAKE_CURRENT_BINARY_DIR}/pistache/build/\n"
       "\t\t  INSTALL_COMMAND\n"
       "\t\t    meson install -C ${CMAKE_CURRENT_BINARY_DIR}/pistache/build/\n"
    )
    else()
      message(ERROR "Meson build system not found.  Pistache requires meson to be installed")
    endif()
  endif()
endif()

