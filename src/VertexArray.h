#pragma once

#include <vector>
#include <GL/glew.h>

class VertexArray {
private:
    GLuint obj;
public:
    VertexArray() {
        glGenVertexArrays(1, &obj);
    }
        void create() {
        glGenVertexArrays(1, &obj);
    }
    void destroy() {
        glDeleteVertexArrays(1, &obj);
    }
    void bind() {
        glBindVertexArray(obj);
    }
    void bindAttribute(GLuint attribute, GLuint buffer, GLuint count, GLuint stride, const GLvoid* offset) {
        glBindVertexArray(obj);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glEnableVertexAttribArray(attribute);
        glVertexAttribPointer(attribute, count, GL_FLOAT, GL_FALSE, stride, offset);
    }
};