#pragma once
#include <GL/glew.h>
#include <vector>
#include "Vertex.h"

class VertexBuffer {
private:
    GLuint obj;
public:
    VertexBuffer() {
        glGenBuffers(1, &obj);
    }
        void create() {
        glGenBuffers(1, &obj);
    }
    void destroy() {
        glDeleteBuffers(1, &obj);
    }
    void uploadData(std::vector<ColouredVertex> data, GLuint length) {
        glBindBuffer(GL_ARRAY_BUFFER, obj);
        glBufferData(GL_ARRAY_BUFFER, length, &data.front(), GL_STATIC_DRAW);
    }
    void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, obj);
    }
    GLuint getObj() { return obj; }
};