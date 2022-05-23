#include <iostream>
#include "GLFW/glfw3.h"
#include <TriangleConfig.h>
#ifdef USE_LOGGER
        #include "logger.h"
#endif

void logStuff()
{   
    #ifdef USE_LOGGER
        Logger::logProjectInfo();
        Logger::log("ciao mamma");
        Logger::warning("yuuuuuuuuuuhuh");
        Logger::error("This  is a random error");
    #else
        std::cout << "Logger is not available!\n";
    #endif
}


int main(int, char **)
{
    logStuff();
    

    GLFWwindow* window;

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    window = glfwCreateWindow( 300, 300, "Test", NULL, NULL );

    while( !glfwWindowShouldClose(window) )
    {
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}