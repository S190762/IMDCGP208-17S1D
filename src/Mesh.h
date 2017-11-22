#pragma once
#include <vector>
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

class Mesh {
private:
    VertexBuffer vertexBuffer;
    VertexArray vertexArray;
    std::vector<ColouredVertex> mesh_data;
public:
    Mesh() {}
    ~Mesh() {}
    void Create(std::vector<ColouredVertex> data) {
        mesh_data = data;
        vertexBuffer.uploadData(mesh_data, mesh_data.size() * sizeof(ColouredVertex));
        vertexArray.bindAttribute(0, vertexBuffer.getObj(), 3, sizeof(ColouredVertex), (const GLvoid*)offsetof(ColouredVertex, x));
        vertexArray.bindAttribute(1, vertexBuffer.getObj(), 3, sizeof(ColouredVertex), (const GLvoid*)offsetof(ColouredVertex, r)); 
    }
    void Update(std::vector<ColouredVertex> data) {
       vertexBuffer.destroy();
       vertexArray.destroy();
       vertexBuffer.create();
       vertexArray.create();
       mesh_data.clear();
    mesh_data = data;
    vertexBuffer.uploadData(mesh_data, mesh_data.size() * sizeof(ColouredVertex));
    vertexArray.bindAttribute(0, vertexBuffer.getObj(), 3, sizeof(ColouredVertex), (const GLvoid*)offsetof(ColouredVertex, x));
    vertexArray.bindAttribute(1, vertexBuffer.getObj(), 3, sizeof(ColouredVertex), (const GLvoid*)offsetof(ColouredVertex, r)); 
    }
    void draw() {
        vertexArray.bind();
        glDrawArrays(GL_TRIANGLES, 0, mesh_data.size());
    }
};