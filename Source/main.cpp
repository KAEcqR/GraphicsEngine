#include <iostream>
#include <vector>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"

using namespace std;

class Circle {
private:
    VAO vao;
    VBO* vbo;
    int vertexCount;
    float radius;
    int res;
public:
    Circle(float positionX, float positionY, float radius, int res) : radius(radius), res(res) {
        vector<float> vertices;
        vertices.push_back(positionX);
        vertices.push_back(positionY);

        for (int i = 0; i <= res; ++i) {
            float angle = 2.0f * 3.14159265358f * (static_cast<float>(i) / res);
            float x = positionX + cos(angle) * radius;
            float y = positionY + sin(angle) * radius;
            vertices.push_back(x);
            vertices.push_back(y);
        }

        vertexCount = vertices.size() / 2;

        vbo = new VBO(vertices);
        vao.Bind();
        vao.LinkVBO(*vbo, 0);
        vao.Unbind();
        vbo->Unbind();
    }

    void Draw(float x, float y, Shader& shader) {
        shader.Activate();

        vector<float> vertices;
        vertices.push_back(x);
        vertices.push_back(y);

        for (int i = 0; i <= res; ++i) { // używamy pola res
            float angle = 2.0f * 3.14159265358f * (static_cast<float>(i) / res);
            float vx = x + cos(angle) * radius; // używamy pola radius
            float vy = y + sin(angle) * radius;
            vertices.push_back(vx);
            vertices.push_back(vy);
        }

        vbo->Bind();
        vbo->Update(vertices);

        vao.Bind();
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    }

};

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int screenWidth = 800;
    int screenHeight = 800;

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Gravity Sim", NULL, NULL);
    if (!window)
    {
        cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();
    glViewport(0, 0, 800, 800);

    Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");
    Shader planetShader("Shaders/default.vert", "Shaders/planet.frag");

    VAO VAO1;
    VAO1.Bind();

    vector<float> planetpos = {0.1f, 0.2f};

    Circle circle(0.3f, 0.4f, 0.1f, 100);
    Circle planet2(planetpos[0], planetpos[1], 0.1f, 100);

    while (!glfwWindowShouldClose(window))
    {
        VAO1.Bind();

        glClear(GL_COLOR_BUFFER_BIT);

        circle.Draw(0.3f, 0.4f, planetShader);
        planet2.Draw(planetpos[0], planetpos[1], shaderProgram);

        planetpos[1] -= 0.01f;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}