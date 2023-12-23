cmake_minimum_required(VERSION 3.10)

project(CustomLS VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Create a static library from custom_ls.c
add_library(custom_ls_lib STATIC src/custom_ls.c)

# Specify include directories for this library
# Here, $<BUILD_INTERFACE:...> and $<INSTALL_INTERFACE:...> are generator expressions that distinguish between build-time and install-time include paths.
target_include_directories(custom_ls_lib PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)

# Add an executable that uses the static library
add_executable(custom_ls main.c)

# Link the static library with the executable
target_link_libraries(custom_ls custom_ls_lib)

# Specify installation paths for the library, executable, and headers
install(TARGETS custom_ls_lib
        EXPORT CustomLSTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)
install(TARGETS custom_ls
        RUNTIME DESTINATION bin)
install(DIRECTORY include/
        DESTINATION include)

# Export the targets to a script
install(EXPORT CustomLSTargets
        FILE CustomLSTargets.cmake
        DESTINATION lib/cmake/CustomLS)

# Create and install the Config.cmake and ConfigVersion.cmake files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    CustomLSConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_file(cmake/CustomLSConfig.cmake.in
    CustomLSConfig.cmake
    @ONLY)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/CustomLSConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/CustomLSConfigVersion.cmake"
    DESTINATION lib/cmake/CustomLS)

# Configure and install the pkg-config file
configure_file(pkgconfig/custom_ls.pc.in custom_ls.pc @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/custom_ls.pc"
        DESTINATION lib/pkgconfig)

# Add a custom target for uninstall
add_custom_target(uninstall COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake")