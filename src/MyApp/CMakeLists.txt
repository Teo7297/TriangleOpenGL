add_executable(${PROJECT_NAME} main.cpp)

if(USE_LOGGER)
    target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Logger)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR}/../)

target_include_directories(${PROJECT_NAME} PUBLIC 
    external/glfw/include
    external/glad/include
    # ${EXTRA_INCLUDE_DIRS}
)

# target_link_directories(${PROJECT_NAME}     # Specifies the paths in which the linker should search for libraries when linking a given target. CMake V3.13+
#     PUBLIC external/glfw/src
#     ${EXTRA_LIB_DIRS}
# )

target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
    glad
    # ${EXTRA_LINKS}
)