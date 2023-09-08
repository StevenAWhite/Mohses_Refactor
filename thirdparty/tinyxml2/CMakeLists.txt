set(GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git)
set(GIT_TAG 8.1.0)

set(FETCH_NAME tinyxml2)
set(PACKAGE_NAME TinyXML2)
set(PACKAGE_PREFIX TINYXML2)
set(PACKAGE_EXPORT tinyxml2::tinyxml2)

find_package(${PACKAGE_NAME} CONFIG REQUIRED GLOBAL )

if(TINYXML2_FOUND)
  set(TINYXML2_LIBRARY "${PACKAGE_EXPORT}" CACHE INTERNAL "The Lirbraries of Tinyxml2" FORCE)
endif()

if (${TinyXML2_FOUND} AND NOT TARGET ${PACKAGE_EXPORT})
  message(STATUS "EXPORTING ${PACKAGE_EXPORT}")
  add_library(${PACKAGE_EXPORT} UNKNOWN IMPORTED GLOBAL)
   
  set_target_properties(${PACKAGE_EXPORT}
  PROPERTIES
  IMPORTED_LOCATION "$<$<CONFIG:Debug>:${PACKAGE_PREFIX}_LIBRARY_RELEASE>$<$<CONFIG:Release>:${PACKAGE_PREFIX}_LIBRARY_DEBUG>"
  INTERFACE_INCLUDE_DIRECTORIES
  ${TinyXML2_INCLUDE_DIR}
  ${TINYXML2_INCLUDE_DIR}
  )
  target_include_directories(${PACKAGE_EXPORT} INTERFACE $<INSTALL_INTERFACE:include> INTERFACE $<BUILD_INTERFACE:${TinyXML2_INCLUDE_DIR}> $<BUILD_INTERFACE:${TINYXML2_INCLUDE_DIR}>)
  message(STATUS "target_link_libraries(${PACKAGE_EXPORT} INTERFACE ${TINYXML2_LIBRARY} ${TinyXML2_LIBRARY})")
elseif(TARGET ${PACKAGE_EXPORT})
  message(STATUS "${PACKAGE_EXPORT} target exists")
endif()

if (NOT ${PACKAGE_NAME}_FOUND)
    message(STATUS "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITROY}. 
    Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
    https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
    https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
else()
  message(STATUS "Found ${PACKAGE_NAME} by find_package")
endif()

