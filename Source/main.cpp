#include <iostream>
#include <vector>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"

using namespace std;

const double G = 6.6743e-11; // m^3 kg^-1 s^-2
const float c = 299792458.0;
float initMass = float(pow(10, 22));
float sizeRatio = 30000.0f;


class Planet {
private:
    VAO vao;
    VBO* vbo;
    int vertexCount;

public:
    float radius;
    int res = 100;
    vector<float> velocity;
    vector<float> position;
    float mass;

    Planet(vector<float> position, float radius, vector<float> velocity, float mass) : radius(radius), velocity(velocity), position(position), mass(mass) {
        vector<float> vertices;
        vertices.push_back(position[0]);
        vertices.push_back(position[1]);

        for (int i = 0; i <= res; ++i) {
            float angle = 2.0f * 3.14159265358f * (static_cast<float>(i) / res);
            float x = position[0] + cos(angle) * radius;
            float y = position[1] + sin(angle) * radius;
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

    void Draw(Shader& shader) {
        shader.Activate();

        vector<float> vertices;
        vertices.push_back(position[0]);
        vertices.push_back(position[1]);

        for (int i = 0; i <= res; ++i) { // używamy pola res
            float angle = 2.0f * 3.14159265358f * (static_cast<float>(i) / res);
            float vx = position[0] + cos(angle) * radius; // używamy pola radius
            float vy = position[1] + sin(angle) * radius;
            vertices.push_back(vx);
            vertices.push_back(vy);
        }

        vbo->Bind();
        vbo->Update(vertices);

        vao.Bind();
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    }

    void Accelerate(float x, float y) {
        velocity[0] += x;
        velocity[1] += y;

        position[0] += velocity[0];
        position[1] += velocity[1];
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

    Planet moon({-0.5f, 0.0f}, 0.1f, {0.0f, 0.0f}, 0.1f);
    Planet earth({0.5f, 0.0f}, 0.1f, {0.0f, 0.0f}, 0.1f);

    double lastTime = glfwGetTime();

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        double dt = currentTime - lastTime;
        lastTime = currentTime;
        glClear(GL_COLOR_BUFFER_BIT);

        moon.Draw(shaderProgram);
        earth.Draw(planetShader);

        moon.Accelerate(-0.001f * dt, 0.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}