#############################
# CMake - Rest Bridge Module - root
#############################

cmake_minimum_required(VERSION 3.25)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
        SET (MOHSES_BUILD_REST_ADAPTER ON)
else()
  option(MOHSES_BUILD_REST_ADAPTER "Toggle building of Mohses Module Manager" ON)
endif()

if (MOHSES_BUILD_REST_ADAPTER AND NOT WIN32)

    project("MOHSES Rest Adapter")

    set(PROJECT_VERSION_MAJOR 1)
    set(PROJECT_VERSION_MINOR 0)
    set(PROJECT_VERSION_PATCH 0)

    site_name(VERSION_HOST) # read hostname to VERSION_HOST

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
    include(Packing)
    #############################
    # CMake Mod Manager root/src
    #############################

    file(GLOB_RECURSE SQLITE_SRCS LIST_DIRECTORIES OFF CONFIGURE_DEPENDS *.cpp)
    file(GLOB_RECURSE SQLITE_HDRS LIST_DIRECTORIES OFF CONFIGURE_DEPENDS *.h)
    set(MODULE_MANAGER_SOURCES src/RESTAdapterMain.cpp ${SQLITE_SRCS} ${SQLITE_HDRS})

    add_executable(mohses_rest_adapter ${MODULE_MANAGER_SOURCES})
    add_executable(Mohses::rest_adapater ALIAS mohses_rest_adapter)

    message(STATUS "Loading Mohses::rest_adapater")

    target_link_libraries(mohses_rest_adapter
            PUBLIC 
            mohses::net
            SQLite::SQLite3
            tinyxml2::tinyxml2
            eProsima::fastcdr
            eProsima::fastrtps
            rapidjson::headers
            pistache::static
            Boost::headers
            Boost::uuid
            Boost::filesystem
            Boost::process
            )
    set(CMAKE_CXX_STANDARD 20) 
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set_target_properties(mohses_rest_adapter PROPERTIES FOLDER ${CMAKE_FOLDER}/modules CXX_STANDARD 20) 

    install(TARGETS mohses_rest_adapter RUNTIME DESTINATION bin)
    install(DIRECTORY ../config DESTINATION bin)

    file(COPY config DESTINATION bin/)

endif(MOHSES_BUILD_REST_ADAPTER  AND NOT WIN32)
