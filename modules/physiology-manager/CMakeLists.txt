#############################
# CMake Mod Manager root/
#############################

cmake_minimum_required(VERSION 3.25)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
        SET (MOHSES_BUILD_physiology_manager ON)
else()
  option(MOHSES_BUILD_physiology_manager "Toggle building of Mohses Module Manager" ON)
endif()

if (MOHSES_BUILD_physiology_manager)
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

        set(physiology_manager_SOURCES src/PhysiologyManager.cpp src/AMM/PhysiologyEngineManager.cpp src/AMM/BiogearsThread.cpp)

        add_executable(mohses_physiology_manager ${physiology_manager_SOURCES})
        add_executable(Mohses::physiology_manager ALIAS mohses_physiology_manager)

        message(STATUS "Loading Mohses::physiology_manager")

        target_link_libraries(mohses_physiology_manager
                PUBLIC
                Threads::Threads
                Biogears::libbiogears
                eProsima::fastrtps
                eProsima::fastcdr
                mohses::net
                SQLite::SQLite3
                tinyxml2::tinyxml2
                Boost::headers
                Boost::filesystem
                Boost::assign
                Boost::uuid
                )

#         stage_biogears_schema(DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#         stage_biogears_data(DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


        set_target_properties(mohses_physiology_manager PROPERTIES FOLDER ${CMAKE_FOLDER}/modules) 

        install(TARGETS mohses_physiology_manager RUNTIME DESTINATION bin)
        install(DIRECTORY ../config DESTINATION bin)

        file(COPY config DESTINATION bin/)
endif(MOHSES_BUILD_physiology_manager)
