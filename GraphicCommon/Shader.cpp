#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Shader.h"


Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) :
    program(glCreateProgram())
{
    std::string vertexCode;
    std::string fragmentCode;

#pragma region READ_FILES
    {
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        //Гарантирует, что объекты потока могут генерировать исключения.
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            //Convert stream into string.
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure&)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
    }
#pragma endregion

    const GLchar* vertexShaderSrc = vertexCode.c_str();
    const GLchar* fragmentShaderSrc = fragmentCode.c_str();

#pragma region COMPILE_AND_LINK_SHADER_PROGRAM
    GLint success;
    GLchar infoLog[512];

    // 1) Vertex Shader.
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    // 4 параметр тут означает что это null-terminated строка.
    // 2 параметр, количество строк в 3-ем параметре.
    glShaderSource(vertex, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertex);

    //Returns a parameter from a shader object.
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 2) Fragment Shader.
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 3) Shader program.
    glAttachShader(this->program, vertex);
    glAttachShader(this->program, fragment);
    glLinkProgram(this->program);

    //Returns a parameter from a program object.
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->program, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Delete the shaders as the program has them now.
    glDeleteShader(vertex);
    glDeleteShader(fragment);
#pragma endregion
}


Shader::~Shader()
{
    glDeleteProgram(this->program);
}


void Shader::use() const
{
    glUseProgram(this->program);
}
