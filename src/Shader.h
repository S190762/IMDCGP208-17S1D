#pragma once
#include <GL/glew.h>
#include <string>

class Shader 
{
private:
     GLuint shader;
public:
    Shader() {}
    Shader(const std::string &code, GLenum type) {
        shader = glCreateShader(type);
        source(code);
        compile();
    }
    ~Shader() {
    }
    GLuint handle() {
        return shader;
    }
    void source(const std::string &code) {
        const char* c = code.c_str();
        glShaderSource(shader, 1, &c, nullptr);
    }
    void compile() {
        glCompileShader(shader);
    }
};
