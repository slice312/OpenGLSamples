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

    // @formatter:off 
    GLfloat vertices[] = {
         0.0f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   //Верхний угол.
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   //Нижний правый угол.
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f    //Нижний левый угол.
    };

    GLuint indices[] = {
        //Помните, что мы начинаем с 0!
        0, 1, 2, //Первый треугольник.
    };
    // @formatter:on 


    GLuint VBO, EBO, VAO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    // 1. Привязываем VAO.
    glBindVertexArray(VAO);
    // 2. Копируем массив вершин в буфер для OpenGL.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. Копируем массив индексов вершин в буфер.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. Устанавливаем указатели на вершинные атрибуты.
    // 4.0 Координаты.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // 4.1 Цвет.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // 5. Отвязываем VAO.
    glBindVertexArray(0);


    //Режим Wireframe.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Для отрисовки только линий, без заливки.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //Вернуть назад.


#pragma region GAME LOOP
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); //Проверяем события и вызываем функции обратного вызова.

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.useProgram();
        GLint offsetUniformLocation = glGetUniformLocation(shader.program, "offset");
        glUniform1f(offsetUniformLocation, 0.45f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
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
