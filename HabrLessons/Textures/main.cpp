#include  <iostream>

//GLEW (нужно подключать до GLFW)
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"


static const GLuint WIDTH = 800, HEIGHT = 600;


void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode);



int main()
{
#pragma region INIT
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL learn", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowPos(window, 200, 100);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);
#pragma endregion GLFW initialization


    glfwSetKeyCallback(window, keyCallback);


    Shader shader("resources/shaders/core.vert",
                  "resources/shaders/core.frag");


    // @formatter:off
    GLfloat texCoords[] = {
        0.0f, 0.0f, // Нижний левый угол 
        1.0f, 0.0f, // Нижний правый угол
        0.5f, 1.0f // Верхняя центральная сторона
    };
    // @formatter:on


#pragma region GAME_LOOP
    while (!glfwWindowShouldClose(window))
    {
        //Check if any events have been activated.
        glfwPollEvents();


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        //Draw.
     


        //Swap the screen buffers.
        glfwSwapBuffers(window);
    }
#pragma endregion rendering and handle events

    glfwTerminate();

    return EXIT_SUCCESS;
}


void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode)
{
    std::cout << "KEY PRESSED\n";
    //Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
    //и приложение после этого закроется.
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
