#include <iostream>
#include <vector>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"

using namespace std;

VAO DrawCircle(float centerX, float centerY, float radius, int res) {
    vector<float> vertices;
    vertices.push_back(centerX);
    vertices.push_back(centerY);

    for (int i = 0; i <= res; ++i) {
        float angle = 2.0f * 3.14159265358f * (static_cast<float>(i) / res);
        float x = centerX + cos(angle) * radius;
        float y = centerY + sin(angle) * radius;
        vertices.push_back(x);
        vertices.push_back(y);
    }

    VBO vbo(vertices); // tworzy bufor wierzchołków
    VAO vao;           // tworzy VAO
    vao.Bind();
    vao.LinkVBO(vbo, 0);
    vao.Unbind();
    vbo.Unbind();

    return vao;
}

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int screenWidth = 800;
    int screenHeight = 800;

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Circle", NULL, NULL);
    if (!window)
    {
        cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 800);

    Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VAO circleVAO = DrawCircle(0.0f, 0.0f, 0.5f, 100);

    // ===== Pętla renderująca =====
    while (!glfwWindowShouldClose(window))
    {
        shaderProgram.Activate();
        VAO1.Bind();

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        circleVAO.Bind();

        glDrawArrays(GL_TRIANGLE_FAN, 0, 102);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    circleVAO.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}