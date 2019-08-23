#include <iostream>

#include "common_funcs.h"
#include "Shader.h"



void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode);



int main()
{
    GLFWwindow* window = common::defaultGlfwWindowInit();

    glfwSetKeyCallback(window, keyCallback);


    Shader shader("resources/shaders/core.vert",
                  "resources/shaders/core.frag");


    // @formatter:off
    GLfloat texCoords[] = {
        0.0f, 0.0f, // Нижний левый угол 
        1.0f, 0.0f, // Нижний правый угол
        0.5f, 1.0f  // Верхняя центральная сторона
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