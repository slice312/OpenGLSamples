#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdarg>

#include "Shader.h"


Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) :
    program(glCreateProgram())
{
    GLuint vertex = compileShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragment = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
    linkProgram(2, vertex, fragment);
}


GLuint Shader::compileShader(const std::string& path, GLenum type)
{
    std::string src = getSourceFromFile(path);
    const GLchar* c_str_src = src.c_str();

    GLuint shader = glCreateShader(type);
    // 2 параметр, количество строк.
    // 4 параметр тут означает что это null-terminated строка.
    glShaderSource(shader, 1, &c_str_src, nullptr);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::" + defineName(type)
            + "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    return shader;
}


std::string Shader::getSourceFromFile(const std::string& path)
{
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::badbit);
    try
    {
        shaderFile.open(path);
        std::stringstream stream;
        stream << shaderFile.rdbuf();
        shaderFile.close();
        return stream.str();
    }
    catch (std::ifstream::failure&)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        std::cout << "FILE: " << path << std::endl;
        return "";
    }
}


void Shader::linkProgram(int count, GLuint shaders...)
{
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++)
    {
        GLuint shader = va_arg(args, GLuint);
        glAttachShader(this->program, shader);
        glDeleteShader(shader); //Delete the shaders as the program has them now.
    }
    va_end(args);

    glLinkProgram(this->program);
    //Returns a parameter from a program object.
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->program, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}


Shader::~Shader()
{
    glDeleteProgram(this->program);
}


void Shader::useProgram() const
{
    glUseProgram(this->program);
}


std::string Shader::defineName(GLenum enm)
{
    switch (enm)
    {
    case GL_VERTEX_SHADER:
        return "VERTEX";
    case GL_FRAGMENT_SHADER:
        return "FRAGMENT";
    default:
        return "";
    }
}
