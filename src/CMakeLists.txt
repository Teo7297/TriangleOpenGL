configure_file(TriangleConfig.h.in TriangleConfig.h)

add_subdirectory(MyApp)

option(USE_LOGGER "Basic logging library" ON)
if(USE_LOGGER)
    add_subdirectory(Logger)
endif()