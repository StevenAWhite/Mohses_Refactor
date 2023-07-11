#############################
# CMake Mod Manager root/
#############################

cmake_minimum_required(VERSION 3.25)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
        SET (MOHSES_BUILD_MODULE_MANAGER ON)
else()
  option(MOHSES_BUILD_MODULE_MANAGER "Toggle building of Mohses Module Manager" ON)
endif()

if (MOHSES_BUILD_MODULE_MANAGER)
        project("MOSHES Module Manager")

        set(PROJECT_VERSION_MAJOR 1)
        set(PROJECT_VERSION_MINOR 0)
        set(PROJECT_VERSION_PATCH 0)

        site_name(VERSION_HOST) # read hostname to VERSION_HOST
        
        set_property(GLOBAL PROPERTY USE_FOLDERS ON)
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

        #############################
        # CMake Mod Manager root/src
        #############################

        set(MODULE_MANAGER_SOURCES src/ModuleManagerMain.cpp src/ModuleManager.cpp)

        add_executable(mohses_module_manager ${MODULE_MANAGER_SOURCES})
        add_executable(Mohses::module_manager ALIAS mohses_module_manager)

        message(STATUS "Loading Mohses::module_manager")

        target_link_libraries(mohses_module_manager
                PUBLIC 
                mohses::net
                SQLite::SQLite3
                tinyxml2::tinyxml2
                Boost::headers
                Boost::uuid
                )
        set_target_properties(mohses_module_manager PROPERTIES FOLDER ${CMAKE_FOLDER}/modules) 

        install(TARGETS mohses_module_manager RUNTIME DESTINATION bin)
        install(DIRECTORY ../config DESTINATION bin)

        file(COPY config DESTINATION bin/)
endif(MOHSES_BUILD_MODULE_MANAGER)
