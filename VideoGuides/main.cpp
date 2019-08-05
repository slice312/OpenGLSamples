#include  <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"


const GLint WIDTH = 800, HEIGHT = 600;


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


    Shader shader("resources/shaders/core.vert",
                  "resources/shaders/core.frag");

	// @formatter:off 
	//Set up vertex data and buffers and attribute pointers.
	GLfloat vertices[] =
	{
		//position                 //color
		-0.5f, -0.5f, 0.0f,        1.0f, 0.0f, 0.0f, //bottom left
		0.5f, -0.5f, 0.0f,         0.0f, 1.0f, 0.0f, //bottom right
		0.0f, 0.5f, 0.0f,          0.0f, 0.0f, 1.0f  //middle top
	};
    // @formatter:on


    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Bind the Vertex Array Object first, then bind and set vertex buffers and attribute pointers.
    glBindVertexArray(VAO);

    //Сделаем буфер текущим.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Передадим информацию о вершинах.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Position attribute.
    // 1 параметр - индекс атрибута вершинного шейдера: layout (location = 0) in vec3 position;
    // 2 параметр - количество компонентов в атрибуте: тип vec3, значит 3;
    // 3 параметр - тип элементов в массиве;
    // 4 параметр - нормализация;
    // 5 параметр - шаг (stride), смещение умноженное на номер вершины (первая вершина индекс 0);
    // 6 параметр - доп смещение (offset). Итоговое смещение определяется так: vertIndex * stride + offset;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    //Color attribute.
    //Тут в 6 параметре смещение 3, потому что массиве vertices[]
    //  цвета записаны с начальным смещением на 3 элемента.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //Unbind, it's always a good thing to unbind any buffer/array to prevent strange bugs.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


#pragma region GAME_LOOP
    while (!glfwWindowShouldClose(window))
    {
        //Check if any events have been activated.
        glfwPollEvents();


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        //Draw.
        shader.useProgram();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);


        //Swap the screen buffers.
        glfwSwapBuffers(window);
    }
#pragma endregion rendering and handle events


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();

    return EXIT_SUCCESS;
}
