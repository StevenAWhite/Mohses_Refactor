#############################
# CMake Standard Library root/src
#############################
macro(install_with_directory)
    set(optionsArgs "")
    set(oneValueArgs "DESTINATION")
    set(multiValueArgs "FILES")
    cmake_parse_arguments(CAS "${optionsArgs}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    foreach(FILE ${CAS_FILES})
        get_filename_component(DIR ${FILE} DIRECTORY)
        INSTALL(FILES ${FILE} DESTINATION ${CAS_DESTINATION}/${DIR})
    endforeach()
endmacro(install_with_directory)

set(AMM_STANDARD_CODE amm/AMM_Standard.cxx amm/AMM_Standard.h amm/AMM_StandardPubSubTypes.cxx amm/AMM_StandardPubSubTypes.h)
set(AMM_EXTENDED_CODE amm/AMM_Extended.cxx amm/AMM_Extended.h amm/AMM_ExtendedPubSubTypes.cxx amm/AMM_ExtendedPubSubTypes.h)
set(DATAMODEL_SOURCES ${AMM_STANDARD_CODE} ${AMM_EXTENDED_CODE})

set(DDS_MANAGER dds_manager)
set(DDS_MANAGER_SOURCES amm/DDSManager.h amm/DDS_Listeners.cpp amm/ListenerInterface.h)
set(DDS_TYPE_SOURCES amm/TopicNames.h amm/AmmDataType.h)
set(UTILITY_SOURCES amm/Utility.cpp amm/Utility.h)


if (MSVC)
    add_library("net" STATIC ${DATAMODEL_SOURCES} ${DDS_TYPE_SOURCES} ${DDS_MANAGER_SOURCES} ${UTILITY_SOURCES})
    set_target_properties("net" PROPERTIES PUBLIC_HEADER
            "net.h;amm/AmmDataType.h;amm/DDSManager.h;amm/DDS_Listeners.h;amm/ListenerInterface.h;amm/TopicNames.h;amm/AMM_Standard.h;amm/AMM_StandardPubSubTypes.h;amm/AMM_Extended.h;amm/AMM_ExtendedPubSubTypes.h;amm/Utility.h;amm/BaseLogger.cpp;amm/BaseLogger.h")
    install(TARGETS net
       EXPORT ${PROJECT_NAME}
       LIBRARY DESTINATION "lib"
       PUBLIC_HEADER DESTINATION "include")
else ()
    add_library("net" SHARED ${DATAMODEL_SOURCES} ${DDS_TYPE_SOURCES} ${DDS_MANAGER_SOURCES} ${UTILITY_SOURCES})
    set_target_properties("net" PROPERTIES PUBLIC_HEADER
            "net.h;amm/AmmDataType.h;amm/DDSManager.h;amm/DDS_Listeners.h;amm/ListenerInterface.h;amm/TopicNames.h;amm/AMM_Standard.h;amm/AMM_StandardPubSubTypes.h;amm/AMM_Extended.h;amm/AMM_ExtendedPubSubTypes.h;amm/Utility.h;amm/BaseLogger.cpp;amm/BaseLogger.h")
    install(TARGETS net
            EXPORT ${PROJECT_NAME}
            LIBRARY DESTINATION "lib"
            PUBLIC_HEADER DESTINATION "include/amm")
endif ()
set_target_properties(net PROPERTIES FOLDER libraries)

add_library(mohses::net ALIAS net)

message(STATUS "Loading Mohses::Net")

target_link_libraries(
        net
        PUBLIC fastrtps
        PUBLIC fastcdr
        PUBLIC Boost::algorithm
        PUBLIC Boost::serialization
)

target_include_directories(net PUBLIC ${PROJECT_SOURCE_DIR}/src)

# Install plog
#install( TARGETS net EXPORT net)
install(DIRECTORY "plog" # source directory
        DESTINATION "include" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.h" # select header files
       )

# Create the cmake file
file(
   WRITE "${CMAKE_CURRENT_BINARY_DIR}/netConfig.cmake"
   "
         include(\"\$\{CMAKE_CURRENT_LIST_DIR\}/netTargets.cmake\")
         set_property(
               TARGET net
               APPEND PROPERTY
                  INTERFACE_INCLUDE_DIRECTORIES \"${HEADER_DIR}\"
         )
      "
)

#export(TARGETS net NAMESPACE mohses:: FILE "${CMAKE_CURRENT_BINARY_DIR}/netTargets.cmake")
#export(PACKAGE net)


install(FILES "${CMAKE_CURRENT_BINARY_DIR}/netConfig.cmake" DESTINATION "lib/cmake/mohses")






