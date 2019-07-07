#include  <iostream>

// GLEW
// #define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"


const GLint WIDTH = 800, HEIGHT = 600;


int main()
{
#pragma region INIT
	glfwInit();
	//Set all the required options for GLFW.
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

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwMakeContextCurrent(window);
	glfwSetWindowPos(window, 200, 100);

	//Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions.
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	//Define the viewport dimensions.
	glViewport(0, 0, screenWidth, screenHeight);
#pragma endregion GLFW initialization

	
	Shader shader("resources/shaders/core.vert",
	                 "resources/shaders/core.frag");

	//Set up vertex data and buffers and attribute pointers.
	GLfloat vertices[] =
	{
		//position          //color
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //bottom left
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //bottom right
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f //middle top
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Bind the Vertex Array Object first, then bind and set vertex buffers and attribute pointers.
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Position attribute.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);

	//Color attribute.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
	                      reinterpret_cast<void*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Unbind, it's always a good thing to unbind any buffer/array to prevent strange bugs.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



#pragma region GAME_LOOP
	while (!glfwWindowShouldClose(window))
	{
		//Check if any events have been activated.
		glfwPollEvents();


		//Render.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//Draw.
		shader.use();
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
