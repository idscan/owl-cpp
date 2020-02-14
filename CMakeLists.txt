###############################################################################
# Project settings
###############################################################################

cmake_minimum_required(VERSION 3.0)

project(owlcpp VERSION 0.3.3.97)

# global definition
set(CMAKE_CXX_STANDARD 11)

###############################################################################
# Initialize Hunter
###############################################################################

# Initialize Hunter
include(cmake/HunterGate.cmake)

HunterGate(
    URL "xxxxxxxxxx"
    SHA1 "xxxxxxxxxx"
)

hunter_add_package(Boost COMPONENTS system)
find_package(Boost CONFIG REQUIRED system)

###############################################################################
# Project installation settings
###############################################################################

set(PROJECT_NAMESPACE "${PROJECT_NAME}::")
set(PROJECT_TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(PROJECT_CONFIG_INSTALL_DIR "lib/cmake/${PROJECT_NAME}")
set(PROJECT_INCLUDE_INSTALL_DIR "include")

###############################################################################
# Internal components
###############################################################################

# Include only library for now.
add_subdirectory(lib)

###############################################################################
# Complete installation
###############################################################################

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")

include(CMakePackageConfigHelpers)

# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY ExactVersion
)

# Use variable 'targets_export_name' to generate configuration file.
set(targets_export_name ${PROJECT_TARGETS_EXPORT_NAME})
configure_file("cmake/Config.cmake.in" "${project_config}" @ONLY)
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${PROJECT_CONFIG_INSTALL_DIR}"
)

# Generate and install target file.
install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${PROJECT_NAMESPACE}"
    DESTINATION "${PROJECT_CONFIG_INSTALL_DIR}"
)

