#############################
# CMake Mod Manager root/
#############################

cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0095 NEW)

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
        add_custom_command(TARGET mohses_module_manager POST_BUILD
                           COMMENT "Staging module_manager Config Files"
                           COMMAND ${CMAKE_COMMAND} -E copy_directory 
                                   ${CMAKE_CURRENT_SOURCE_DIR}/config/
                                   $<TARGET_FILE_DIR:mohses_module_manager>/config
                          ) 
        message(STATUS "Loading Mohses::module_manager")

        target_link_libraries(mohses_module_manager
                PUBLIC 
                mohses::net
                SQLite::SQLite3
                tinyxml2::tinyxml2
                Boost::headers
                Boost::uuid
                )
        set_target_properties(mohses_module_manager PROPERTIES 
                 FOLDER ${CMAKE_FOLDER}/modules
                 INSTALL_RPATH "\${ORIGIN}:\${ORIGIN}/../lib:\${ORIGIN}/lib"
         ) 

        install(TARGETS mohses_module_manager RUNTIME DESTINATION bin)
        install(DIRECTORY config DESTINATION bin)

endif(MOHSES_BUILD_MODULE_MANAGER)
