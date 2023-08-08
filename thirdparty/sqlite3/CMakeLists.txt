cmake_minimum_required(VERSION 3.25.0)

include (FetchContent)

function(guarantee_sqlite3_availability)
   set(GIT_REPOSITORY https://github.com/azadkuh/sqlite-amalgamation.git )
   set(GIT_TAG master)
   set(PACKAGE_NAME SQLite3)
   set(EXPORT_NAME SQLite::SQLite3)
   set(PACKAGE_PREFIX SQLITE)

   cmake_parse_arguments("${PACKAGE_NAME}" "REQUIRED" "" ""  ${ARGN})
   find_package(${PACKAGE_NAME} QUIET GLOBAL)
   Set(FETCHCONTENT_QUIET FALSE)
   if ( NOT ${PACKAGE_NAME}_FOUND)
        if (MOHSES_FETCH_THIRDPARTY)
            if (BUILD_THIRDPARTY_TEST)
                 option(BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST "Build ${PACKAGE_NAME} sample project for testing" ON)
            endif()
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PACKAGE_NAME}")
            FetchContent_Declare(
                ${PACKAGE_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY} 
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE  TRUE
            )
            message(STATUS "${PACKAGE_NAME} not found Fetching ${GIT_TAG}")
          
            FetchContent_MakeAvailable(${PACKAGE_NAME})
            if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}-extra.cmake AND
            NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}Extra.cmake)

            set(${PACKAGE_PREFIX}_INCLUDE_DIR $<INSTALL_INTERFACE:include>$<BUILD_INTERFACE:${${PACKAGE_NAME}_SOURCE_DIR}>)
            set(${PACKAGE_PREFIX}_INCLUDE_DIRS $<INSTALL_INTERFACE:include>$<BUILD_INTERFACE:${${PACKAGE_NAME}_SOURCE_DIR}>)
               file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}-extra.cmake                                
               "
                  if(\"\${${PACKAGE_PREFIX}_INCLUDE_DIR}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_INCLUDE_DIR ${${PACKAGE_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_INCLUDE_DIRS}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_INCLUDE_DIRS ${${PACKAGE_PREFIX}_INCLUDE_DIRS})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY_DEBUG}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARY ${${PACKAGE_PREFIX}_LIBRARY_DEBUG})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY_RELEASE}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARY_RELEASE  ${${PACKAGE_PREFIX}_LIBRARY_RELEASE})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARIES}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARIES  ${SQLite3_LIBRARIES})
                  endif()
               ")
            endif()

            if (NOT TARGET ${EXPORT_NAME}
            )
              add_library(${EXPORT_NAME} INTERFACE IMPORTED GLOBAL SQLite3)
              
              set_target_properties(${EXPORT_NAME}
              PROPERTIES
              INTERFACE_INCLUDE_DIRECTORIES
              ${${PACKAGE_NAME}_SOURCE_DIR}
              )
              target_include_directories(${EXPORT_NAME} INTERFACE $<INSTALL_INTERFACE:include>$<BUILD_INTERFACE:${${PACKAGE_NAME}_SOURCE_DIR}>)
              target_link_libraries(${EXPORT_NAME} INTERFACE SQLite3)
            endif()
            install(TARGETS ${PACKAGE_NAME} EXPORT ${PACKAGE_NAME})  
            export(TARGETS  ${PACKAGE_NAME} FILE ${PACKAGE_NAME}-targets.cmake)
            if (BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(${PACKAGE_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PACKAGE_NAME}.cpp)
                set_target_properties(${PACKAGE_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(${PACKAGE_NAME}_test PRIVATE ${EXPORT_NAME})
                # target_include_directories(${PACKAGE_NAME}_test PRIVATE $<INSTALL_INTERFACE:include>$<BUILD_INTERFACE:${${PACKAGE_NAME}_SOURCE_DIR}>)
            endif()
        endif()
   endif()

   find_package(${PACKAGE_NAME} REQUIRED GLOBAL)

   if (NOT ${PACKAGE_NAME}_FOUND)
    message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITROY}. 
      Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
      https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
      https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
   endif()


endfunction()

guarantee_sqlite3_availability()
