#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
private:
    GLuint prog;
public:
    ShaderProgram() {}
    ShaderProgram(Shader vert, Shader frag) {
        prog = glCreateProgram();
        attach(vert);
        attach(frag);
        link();
    }
    void attach(Shader v) {
        glAttachShader(prog, v.handle());
    }
    void use() {
        glUseProgram(prog);
    }
    void link() {
        glLinkProgram(prog);
    }
    GLuint getUniformLoc(std::string name) {
        return glGetUniformLocation(prog, name.c_str());
    }
    void uploadUniform(GLuint location, int data) {
        glUniform1i(location, data);
    }
    void uploadUniform(GLuint location, glm::mat4 data) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
    }
};