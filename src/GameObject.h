#pragma once
#include "Shader.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameObject {
private:
    ShaderProgram* sp;
    Mesh* m;
    glm::mat4 model = glm::mat4(1);
public:
    GameObject() {}
    ~GameObject() {}
    void Create(ShaderProgram *a, Mesh *b) {
        sp = a;
        m = b;
    }
    void Update(ShaderProgram *a, Mesh *b) {
        sp = nullptr;
        m = nullptr;
        sp = a;
        m = b;
    }
    void SetRotation(float ammount, glm::vec3 axis) {
        model = glm::rotate(model, ammount, axis);
    }
    void SetPosition(glm::vec3 pos) {
        model = glm::translate(model, pos);
    }
    void SetScale(glm::vec3 scale) {
        model = glm::scale(model, scale);
    }
    void UploadPV(glm::mat4 mat) {
        sp->use();
        sp->uploadUniform(sp->getUniformLoc("projViewMatrix"), mat);
    }
    void DrawObject() {
        sp->use();
        sp->uploadUniform(sp->getUniformLoc("modelMatrix"), model);
        m->draw();
    }
};