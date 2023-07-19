cmake_minimum_required(VERSION 3.20.0)

include (FetchContent)

function(gaurentee_foonathan_memory_availability)
    set(GIT_REPOSITORY  https://github.com/foonathan/memory.git )
    set(GIT_TAG "v0.7-3")
    set(PROJECT_NAME foonathan_memory)
    set(PROJECT_PREFIX FOONATHAN_MEMORY)
    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_${PROJECT_NAME}_AVAILABILITY_TEST "Build ${PROJECT_NAME} sample project for testing" ON)
    endif()
    cmake_parse_arguments("${PROJECT_NAME}" "REQUIRED" "" ""  ${ARGN})
    find_package(${PROJECT_NAME} QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    
    if ( NOT ${PROJECT_NAME}_FOUND )
        set(CMAKE_FOLDER "${CMAKE_FOLDER}/FooNathan")
        FetchContent_Declare(
            ${PROJECT_NAME}
            GIT_REPOSITORY ${GIT_REPOSITORY}
            GIT_TAG ${GIT_TAG}
            GIT_PROGRESS TRUE
            OVERRIDE_FIND_PACKAGE  TRUE
            CMAKE_ARGS
                -D${PROJECT_PREFIX}_BUILD_EXAMPLES=OFF
                -D${PROJECT_PREFIX}_BUILD_TESTS=OFF
                -D${PROJECT_PREFIX}_BUILD_TOOLS=ON
        )
        
        message(STATUS "${PROJECT_NAME} not found Fetching ${GIT_TAG}")            
        FetchContent_MakeAvailable(${PROJECT_NAME})

            if (TARGET SQLite3)
               message(FATAL_ERROR "WE HAVE A TARGET SQLite3")
            endif()

            if (TARGET SQLite::SQLite3)
               message(FATAL_ERROR"WE HAVE A TARGET SQLite::SQLite3")
            endif()


        if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PROJECT_NAME}-extra.cmake AND
            NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PROJECT_NAME}Extra.cmake)

            

            get_target_property(${PROJECT_PREFIX}_INCLUDE_DIR  ${PROJECT_NAME} INCLUDE_DIRECTORIES)
            get_target_property(${PROJECT_PREFIX}_LIBRARIES  ${PROJECT_NAME} OUTPUT_NAME)

            file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PROJECT_NAME}-extra.cmake                                
            "
               if(${PROJECT_PREFIX}_INCLUDE_DIR STREQUAL \"\" AND TARGET  ${PROJECT_NAME})
                 set(${PROJECT_PREFIX}_INCLUDE_DIR ${${PROJECT_PREFIX}_INCLUDE_DIR})
               endif()
               if(${PROJECT_PREFIX}_INCLUDE_DIRS} STREQUAL \"\" AND TARGET  ${PROJECT_NAME})
                 set(${PROJECT_PREFIX}_INCLUDE_DIRS ${${PROJECT_PREFIX}_INCLUDE_DIRS})
               endif()
               if(${PROJECT_PREFIX}_LIBRARY_DEBUG} STREQUAL \"\" AND TARGET  ${PROJECT_NAME})
                 set(${PROJECT_PREFIX}_LIBRARY ${${PROJECT_PREFIX}_LIBRARY_DEBUG})
               endif()
               if(${PROJECT_PREFIX}_LIBRARY_RELEASE} STREQUAL \"\" AND TARGET  ${PROJECT_NAME})
                 set(${PROJECT_PREFIX}_LIBRARY_RELEASE  ${${PROJECT_PREFIX}_LIBRARY_RELEASE})
               endif()
               if(${PROJECT_PREFIX}_LIBRARIES} STREQUAL \"\" AND TARGET  ${PROJECT_NAME})
                 set(${PROJECT_PREFIX}_LIBRARIES  ${PROJECT_PREFIX}_LIBRARIES )
               endif()
            ")
        endif()
        install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME})  
        export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}-targets.cmake)
        if (BUILD_${PROJECT_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
            add_executable(${PROJECT_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PROJECT_NAME}.cpp)
            set_target_properties(${PROJECT_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
            target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})            
        endif()

        if (${PROJECT_NAME}_REQUIRED AND NOT ${PROJECT_NAME}_FOUND)
            message(FATAL_ERROR "Unable to find ${PROJECT_NAME} or fetch it from ${GIT_REPOSITROY}. 
            Check your network connection or install the ${PROJECT_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
            https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
            https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
        endif()
    endif()
endfunction()

gaurentee_foonathan_memory_availability()
