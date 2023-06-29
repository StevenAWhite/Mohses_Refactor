cmake_minimum_required(VERSION 3.20.0)

function(gaurentee_foonathan_memory_availability)
    set(GIT_REPOSITORY  https://github.com/foonathan/memory.git )
    set(GIT_TAG "v0.7-3")

    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_foonathan_memory_AVAILABILITY_TEST "Build foonathan_memory sample project for testing" ON)
    endif()
    cmake_parse_arguments("foonathan_memory" "REQUIRED" "" ""  ${ARGN})
    find_package(foonathan_memory QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    
    if ( NOT foonathan_memory_FOUND )
        set(CMAKE_FOLDER "${CMAKE_FOLDER}/FooNathan")
        FetchContent_Declare(
            foonathan_memory
            GIT_REPOSITORY ${GIT_REPOSITORY}
            GIT_TAG ${GIT_TAG}
            GIT_PROGRESS TRUE
            OVERRIDE_FIND_PACKAGE  TRUE
            CMAKE_ARGS
                -DFOONATHAN_MEMORY_BUILD_EXAMPLES=OFF
                -DFOONATHAN_MEMORY_BUILD_TESTS=OFF
                -DFOONATHAN_MEMORY_BUILD_TOOLS=ON
        )
        
        message(STATUS "foonathan_memory not found Fetching ${GIT_TAG}")            
        FetchContent_MakeAvailable(foonathan_memory)      
        install(TARGETS foonathan_memory EXPORT foonathan_memory)  
        export(TARGETS foonathan_memory FILE foonathan_memory-targets.cmake)
        if (BUILD_foonathan_memory_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
            add_executable(foonathan_memory_test ${PROJECT_SOURCE_DIR}/cmake/tests/foonathan_memory.cpp)
            set_target_properties(foonathan_memory_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
            target_link_libraries(foonathan_memory_test PRIVATE foonathan_memory)            
        endif()

        if (foonathan_memory_REQUIRED AND NOT foonathan_memory_FOUND)
            message(FATAL_ERROR "Unable to find foonathan_memory or fetch it from ${GIT_REPOSITROY}. 
            Check your network connection or install the foonathan_memory package and configure your CMAKE_PREFIX_PATH to ensure visibility
            https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
            https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
        endif()
    endif()
endfunction()
