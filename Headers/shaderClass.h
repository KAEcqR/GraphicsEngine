#ifndef SHADERCLASS_H
#define SHADERCLASS_H

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
    public:
        GLuint ID;
        Shader(const char* vertexPath, const char* fragmentPath);

    void Activate();
    void Delete();
};

#endif