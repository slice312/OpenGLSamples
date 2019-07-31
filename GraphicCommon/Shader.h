#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>


class Shader
{
private:
    const GLchar* vertexShaderSrc;
    const GLchar* fragmentShaderSrc;

public:
    const GLuint program;

    //Constructor generates the shader on the fly.
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    //Uses the current shader program.
    void useProgram() const;

private:

    void loadFromFiles(const std::string& vertexPath, const std::string& fragmentPath);

};


#endif // SHADER_H_INCLUDED
