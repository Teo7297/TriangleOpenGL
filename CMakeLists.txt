cmake_minimum_required(VERSION 3.0.0)
project(Triangle VERSION 0.1.0)
set(PROJECT_OWNER "Matteo Cavagnino")

add_subdirectory(src)

#################### SUBMODULES #################################

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(external/glfw)
#################### END OF SUMBMODULES #########################


################### INSTALLATION ################################

#CMake install
install(TARGETS ${PROJECT_NAME} DESTINATION bin)                                    # exe file goes to bin filder
install(FILES "${PROJECT_BINARY_DIR}/src/TriangleConfig.h" DESTINATION include)        # config file goes to include folder

# To install the app run cmake install and add the bin folder to the env var
# C:\Program Files (x86)\ImGUITest\bin

message(STATUS "helll ${CMake_SOURCE_DIR}")
# CPack install
include (InstallRequiredSystemLibraries)


set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Licence.txt")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_NAME "Triangle")
set(CPACK_PACKAGE_VENDOR "Teoware")

if(WIN32 AND NOT UNIX)
    #set(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}\\\\utilities\\\\icon.ico") #! not working, icon is set in the add_executable second parameter
    set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\${PROJECT_NAME}.exe")
    set(CPACK_NSIS_DISPLAY_NAME "${PROJECT_NAME} ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
    set(CPACK_NSIS_MODIFY_PATH ON)

endif()

set(CPACK_NSIS_CREATE_ICONS_EXTRA
    "CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Triangle.lnk' '$INSTDIR\\\\bin\\\\${PROJECT_NAME}.exe'"
)
set(CPACK_NSIS_DELETE_ICONS_EXTRA
    "Delete '$SMPROGRAMS\\\\$START_MENU\\\\Triangle.lnk'"
)
set(CPACK_PACKAGE_EXECUTABLES "Triangle" "Triangle")
set(CPACK_CREATE_DESKTOP_LINKS "Triangle")


include(CPack)

# To install run the .exe file generated in build folder
################### END OF INSTALLATION #########################