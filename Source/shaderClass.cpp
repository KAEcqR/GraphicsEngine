#include "shaderClass.h"

std::string get_file_contents(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "ERROR: Cannot open file: " << filename << std::endl;
        std::exit(EXIT_FAILURE);
    }
    in.seekg(0, std::ios::end);
    std::string contents(in.tellg(), '\0');
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
}

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode = get_file_contents(vertexPath);
    std::string fragmentCode = get_file_contents(fragmentPath);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint offsetLocation = glGetUniformLocation(ID, "offset");
}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}