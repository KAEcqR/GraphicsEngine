#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <vector>

class VBO {
public:
    GLuint ID;

    // Konstruktor przyjmuje teraz referencję do vectora, nie wskaźnik
    VBO(const std::vector<float>& vertices);

    void Bind();
    void Unbind();
    void Delete();
};

#endif