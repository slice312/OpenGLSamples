#include <iostream>

#include <SOIL2/SOIL2.h>

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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Load, create texture and generate mipmaps.
    int width, height;
    unsigned char* image = SOIL_load_image("resources/images/image2.png",
        &width, &height, nullptr, SOIL_LOAD_RGBA);


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