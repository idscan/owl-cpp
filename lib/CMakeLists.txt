cmake_minimum_required(VERSION 3.0)

###############################################################################
# Target settings
###############################################################################

set(PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

get_filename_component(LIBRARY_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)

add_library(${LIBRARY_NAME} OBJECT lib_info.cpp)
target_include_directories(${LIBRARY_NAME} PRIVATE
    "${PROJECT_INCLUDE_DIR}"
    "${Boost_INCLUDE_DIR}"
)
target_compile_definitions(${LIBRARY_NAME} PRIVATE
    "OWLCPP_BUILD=0"
    "OWLCPP_NAME=${PROJECT_NAME}"
    "OWLCPP_DESCRIPTION=C++ library for working with OWL ontologies"
    "OWLCPP_VERSION_1=${PROJECT_VERSION_MAJOR}"
    "OWLCPP_VERSION_2=${PROJECT_VERSION_MINOR}"
    "OWLCPP_VERSION_3=${PROJECT_VERSION_PATCH}"
    "OWLCPP_VERSION_EXTRA=${PROJECT_VERSION_TWEAK}"
    "OWLCPP_VERSION_DIRTY=0"
)

target_link_libraries(${LIBRARY_NAME} Boost::boost)

# Generate public header list.
file(GLOB LIBRARY_HEADER_FILES
    "${PROJECT_INCLUDE_DIR}/${PROJECT_NAME}/*.hpp"
)

# Install common header files.
foreach(_folder_name detail terms)
    install(
        DIRECTORY "${PROJECT_INCLUDE_DIR}/${PROJECT_NAME}/${_folder_name}"
        DESTINATION "${PROJECT_INCLUDE_INSTALL_DIR}/${PROJECT_NAME}"
    )
endforeach()

install(
    FILES ${LIBRARY_HEADER_FILES}
    DESTINATION "${PROJECT_INCLUDE_INSTALL_DIR}/${PROJECT_NAME}"
)

###############################################################################
# Library components
###############################################################################

# Include private headers.
include_directories(${CMAKE_CURRENT_LIST_DIR})

# RDF store and core functionality.
add_subdirectory(rdf)

option(BUILD_IO "Build OWL/RDF parser" ON)
if(BUILD_IO)
    add_subdirectory(io)
endif()

option(BUILD_LOGIC "Build axiom generator" ON)
if(BUILD_LOGIC)
    add_subdirectory(logic)
endif()
