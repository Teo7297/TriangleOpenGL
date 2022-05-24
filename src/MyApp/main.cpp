#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#pragma warning( disable : 4244 )

#include <GLFW/glfw3.h>
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std::chrono;

typedef high_resolution_clock Time;

float Xoffset = 0.f;
float Yoffset = 0.f;
float speed = .001f;
bool goingLeft = true;
auto oldTime = Time::now();
float deltaTime;

struct TriangleShape
{
    GLfloat leftVertexX = .5f;
    GLfloat leftVertexY = -.5f;
    GLfloat rightVertexX = -.5f;
    GLfloat rightVertexY = -.5f;
    GLfloat topVertexX = .0f;
    GLfloat topVertexY = .5f;
};

void drawTriangle(TriangleShape *triangle)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(triangle->leftVertexX, triangle->leftVertexY);
    glVertex2f(triangle->rightVertexX, triangle->rightVertexY);
    glVertex2f(triangle->topVertexX, triangle->topVertexY);
    glEnd();
}

void updateTriangle(TriangleShape *triangle)
{
    triangle->leftVertexX -= Xoffset;
    triangle->leftVertexY -= Yoffset;
    triangle->rightVertexX -= Xoffset;
    triangle->rightVertexY -= Yoffset;
    triangle->topVertexX -= Xoffset;
    triangle->topVertexY -= Yoffset;

    if (triangle->leftVertexX <= 0.0f)
        goingLeft = false;
    if (triangle->rightVertexX >= 0.0f)
        goingLeft = true;

    if (goingLeft)
    {
        Xoffset = speed * deltaTime;
    }
    else
    {
        Xoffset = -speed * deltaTime;
    }
}

void updateTime()
{
    auto currentTime = Time::now();
    duration<float> delta = currentTime - oldTime;
    deltaTime = duration_cast<milliseconds>(delta).count();
    oldTime = currentTime;
}

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    TriangleShape *triangle{new TriangleShape};

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // update
        updateTime();
        updateTriangle(triangle);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        drawTriangle(triangle);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete triangle;
    triangle = nullptr;

    glfwTerminate();
}