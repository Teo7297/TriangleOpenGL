add_executable(${PROJECT_NAME} main.cpp)

find_package(openGL)

if(USE_LOGGER)
    list(APPEND EXTRA_LINKS Logger)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR}/../)

target_include_directories(${PROJECT_NAME} PUBLIC 
    external/glfw/include
    external/glad/include
)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
    opengl32
    glfw
    glad
    ${EXTRA_LINKS}
)