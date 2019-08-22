#include <iostream>

#include "common_funcs.h"
#include "Shader.h"

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "SOIL2/SOIL2.h"



int main()
{
    GLFWwindow* window = common::defaultGlfwWindowInit();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("resources/shaders/core.vert",
                  "resources/shaders/core.frag");

    // @formatter:off 
    //Set up vertex data and buffers and attribute pointers.
    GLfloat vertices[] =
    {
        //position              //color                 //texture coordinates
        0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f,       1.0f, 1.0f, //top right
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,       1.0f, 0.0f, //bottom right
        -0.25f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,       0.0f, 0.0f, //bottom left
        -0.25f, 0.5f, 0.0f,     1.0f, 1.0f, 0.0f,       0.0f, 1.0f  //top left
    };


    GLuint indices[] =
    {
        // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    // @formatter:on


    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Position attribute.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    //Color attribute.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //Texture Coordinate attribute.
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          reinterpret_cast<void*>(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);


    //Unbind VAO.
    glBindVertexArray(0);


    //Load and create a texture.
    GLuint texture;

    int width, height;


    // ===================
    // Texture
    // ===================
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //Set our texture parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Set texture filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Load, create texture and generate mipmaps.
    unsigned char* image = SOIL_load_image("resources/images/image2.png",
                                           &width, &height, nullptr, SOIL_LOAD_RGBA);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    //Game loop
    while (!glfwWindowShouldClose(window))
    {
        //Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render, clear the color buffer.
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        //Draw the triangle.
        shader.useProgram();

        glm::mat4 transform(1);
        transform = glm::translate(transform, glm::vec3(0.2f, -0.3f, 0.0f));
        transform = glm::rotate(transform, (GLfloat) glfwGetTime() * 4.0f, glm::vec3(0.0f, 0.0f, 1.0f));

        GLint transformLocation = glGetUniformLocation(shader.program, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(shader.program, "ourTexture"), 0);

        // Draw container
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    //Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    //Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();

    return EXIT_SUCCESS;
}
