#ifndef COMMON_FUNCS_H_INCLUDED
#define COMMON_FUNCS_H_INCLUDED

/*
 * Содержит общие функции которые обычно копипастятся из проекта в проект.
 *
 * Подключается во все проекты OpenGL, чтобы каждый раз при создании нового проекта
 * не добавлять в зависимости хедеры и библиотеки GLEW, GLFW, SDL и т.д.
 */


//GLEW (нужно подключать до GLFW)
#define GLEW_STATIC
#include "../External Libraries/GLEW/include/GL/glew.h"

//GLFW
#include "../External Libraries/GLFW32/include/GLFW/glfw3.h"


namespace common
{
    GLFWwindow* defaultGlfwWindowInit();
}


#endif // COMMON_FUNCS_H_INCLUDED