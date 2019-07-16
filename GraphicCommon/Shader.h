#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>


class Shader
{
public:
    const GLuint program;

    //Constructor generates the shader on the fly.
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    ~Shader();

    //Uses the current shader program.
    void use() const;
};


#endif // SHADER_H_INCLUDED
