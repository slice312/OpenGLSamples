#include  <iostream>

// GLEW
// #define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>


const GLint WIDTH = 800, HEIGHT = 600;
const GLchar* vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main() \n"
	"{ \n"
	"    gl_Position = vec4(position.x, position.y, position.z, 1.0); \n"
	"}";

const GLchar* fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 color; \n"
	"void main() \n"
	"{  \n"
	"    color = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
	"}";


int main()
{
#pragma region INIT
	glfwInit();
	// Set all the required options for GLFW
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

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);
#pragma endregion GLFW initialization


#pragma region SHADER_PROGRAM
	GLint success;
	GLchar infoLog[512];

	//Create and compile vertex shader.
	// 4 параметр тут означает что это null terminated строка.
	// 2 параметр, количество строк в 3-ем параметре.
	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	//Returns a parameter from a shader object.
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//Create and compile fragment shader.
	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//Create program, attach shaders to it, and link it.
	const GLuint shadeProgram = glCreateProgram();
	glAttachShader(shadeProgram, vertexShader);
	glAttachShader(shadeProgram, fragmentShader);
	glLinkProgram(shadeProgram);

	//Returns a parameter from a program object.
	glGetProgramiv(shadeProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shadeProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//Delete the shaders as the program has them now.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
#pragma endregion compile and link shaders



	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // bottom left
		0.5f, -0.5f, 0.01,
		0.0f, 0.5f, 0.0f
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);

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


		glUseProgram(shadeProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);


		//draw OpenGL
		glfwSwapBuffers(window);
	}
#pragma endregion rendering and handle events

	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shadeProgram);
	glfwTerminate();

	return EXIT_SUCCESS;
}
