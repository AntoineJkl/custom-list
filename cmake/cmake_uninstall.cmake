# check if the file 'install_manifest.txt' exists
if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt")
    # read the install_manifest.txt file
    file(READ "${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt" contents)
    string(REGEX REPLACE "\n" ";" files "${contents}")

    # iterate over each line and remove the file
    foreach(file ${files})
        message(STATUS "Removing file: ${file}")
        if(EXISTS "${file}")
            file(REMOVE "${file}")
        else()
            message(STATUS "File already removed: ${file}")
        endif()
    endforeach()
endif()