#############################
# CMake Mod Manager root/
#############################

cmake_minimum_required(VERSION 3.25)

project("MOSHES Module Manager")

set(VERSION_TYPE "beta" CACHE STRING "version type" FORCE)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 0)
site_name(VERSION_HOST) # read hostname to VERSION_HOST
set(VERSION_HOST "${VERSION_HOST}" CACHE STRING "host of build" FORCE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#############################
# CMake Mod Manager root/src
#############################

set(MODULE_MANAGER_SOURCES src/ModuleManagerMain.cpp src/ModuleManager.cpp)

add_executable(mohses_module_manager ${MODULE_MANAGER_SOURCES})
add_executable(Mohses::module_manager ALIAS mohses_module_manager)
target_link_libraries(mohses_module_manager
        PUBLIC 
        mohses::net
        SQLite::SQLite3
        tinyxml2::tinyxml2
        Boost::headers
        Boost::uuid
        )
set_target_properties(mohses_module_manager PROPERTIES FOLDER modules) 

install(TARGETS mohses_module_manager RUNTIME DESTINATION bin)
install(DIRECTORY ../config DESTINATION bin)

file(COPY config DESTINATION bin/)
