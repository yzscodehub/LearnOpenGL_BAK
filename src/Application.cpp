#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
    GLFWwindow* window;

    // 初始化glfw
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // 初始化glew
    glewExperimental = true;    // needed for core profile
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error glewInit" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


    /// 矩形
    /// 方法1：
    /*
    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,

         0.5f,  0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f,
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    */

    /// 方法2：
    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Have to set VAO before binding attributes
    /*unsigned int VAO;
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));*/
    VertexArray VA; 
    VertexBuffer VB(positions, 2 * 4 * sizeof(float));
    IndexBuffer IB(indices, 6);

    VertexArrayLayout layout;
    layout.Push<float>(2);
    VA.AddBuffer(VB, layout);


    Shader shader("res/shaders/Basic.shader");
    float red = 0.0f;
    float step = 0.05f;

    IB.Bind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS)
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // set shader and set uniform color
        //GLCall(glUseProgram(shaderProgram));
        // set uniform color
        shader.SetUniform4f("u_Color", red, 0.3f, 0.8f, 1.0f);

        // Instead of binding vertex buffer, attrib pointer, just bind Vertex Array Object
        //GLCall(glBindVertexArray(VAO));
        // Bind index buffer
        //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        if (red < 0.0f || red > 1.0f)
            step *= -1.0;
        red += step;
    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    return 0;
}
