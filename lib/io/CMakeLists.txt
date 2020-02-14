cmake_minimum_required(VERSION 3.0)

###############################################################################
# Third-party libraries
###############################################################################

hunter_add_package(Boost COMPONENTS filesystem)
find_package(Boost CONFIG REQUIRED filesystem)

hunter_add_package(raptor2)
find_package(raptor2 CONFIG REQUIRED)

###############################################################################
# Target settings
###############################################################################

get_filename_component(LIBRARY_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)

# Generate source file list.
set(LIBRARY_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}")
file(GLOB LIBRARY_SOURCE_FILES
    "${LIBRARY_SOURCE_DIR}/*.cpp"
)

# Generate private header list.
set(LIBRARY_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}")
file(GLOB LIBRARY_HEADER_FILES
    "${LIBRARY_INCLUDE_DIR}/*.hpp"
)

add_library(${LIBRARY_NAME} STATIC
    ${LIBRARY_SOURCE_FILES}
    ${LIBRARY_HEADER_FILES}
)
# Apply Boost naming convention.
if(Boost_USE_MULTITHREADED)
    set(MULTITHREADED_POSTFIX "-mt")
else()
    set(MULTITHREADED_POSTFIX)
endif()
set_target_properties(${LIBRARY_NAME} PROPERTIES
    DEBUG_POSTFIX "-d"
    OUTPUT_NAME "${PROJECT_NAME}_${LIBRARY_NAME}${MULTITHREADED_POSTFIX}"
)
target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:> # Project level include directory will do.
)
target_link_libraries(${LIBRARY_NAME} PUBLIC
    Boost::filesystem
)
target_link_libraries(${LIBRARY_NAME} PRIVATE
    raptor2
)

# IO needs core functionality
add_dependencies(${LIBRARY_NAME} rdf)

###############################################################################
# Installation settings
###############################################################################

# Install library files and update target file.
install(
    TARGETS ${LIBRARY_NAME}
    EXPORT "${PROJECT_TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${PROJECT_INCLUDE_INSTALL_DIR}"
)

# Install header files as command above only installs library files.
install(
    DIRECTORY "${PROJECT_INCLUDE_DIR}/${PROJECT_NAME}/${LIBRARY_NAME}"
    DESTINATION "${PROJECT_INCLUDE_INSTALL_DIR}/${PROJECT_NAME}"
)
