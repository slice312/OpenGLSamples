#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED


#include <string>

#include "common_funcs.h"



class Shader
{
public:
    const GLuint program;

    //Constructor generates the shader on the fly.
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    //Uses the current shader program.
    void useProgram() const;

private:

    static GLuint compileShader(const std::string& path, GLenum type);
    void linkProgram(int count, GLuint shaders...);
    
    static std::string getSourceFromFile(const std::string& path);

    static std::string defineName(GLenum enm);
};


#endif // SHADER_H_INCLUDED