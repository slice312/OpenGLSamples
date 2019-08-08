#include <iostream>

//GLEW (нужно подключать до GLFW)
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"


void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode);


static const GLuint WIDTH = 800, HEIGHT = 600;


int main()
{
#pragma region INIT
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //Выключение возможности изменения размера окна.

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
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
#pragma endregion

    
    glfwSetKeyCallback(window, keyCallback);


    Shader shader("resources/shaders/core.vert",
                  "resources/shaders/core.frag");


    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };


    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    // 0. Копируем массив с вершинами в буфер OpenGL.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 1. Затем установим указатели на вершинные атрибуты.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);
    // 2. Используем нашу шейдерную программу.
    shader.useProgram();
    // 4. Отвязываем VAO.
    glBindVertexArray(0);

#pragma region GAME LOOP
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); //Проверяем события и вызываем функции обратного вызова.

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glBindVertexArray(0);
    }
#pragma endregion

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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
