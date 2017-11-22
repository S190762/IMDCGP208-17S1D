#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Shader.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Util.h"
#include "Window.h"
#include "GameObject.h"
#include "Camera.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "ext/OBJLoader.h"

Window window;
Shader frag(readfromfile("res/shader.frag"), GL_FRAGMENT_SHADER);
Shader vertex(readfromfile("res/shader.vert"), GL_VERTEX_SHADER);
ShaderProgram sp(vertex, frag);

std::string loadedObject = "res/ak47.obj";

Camera c;
objl::Loader loader;
bool load = false;

void inputFunc() {
    c.SetCameraSpeed(2.5f * window.getDT());
    if(glfwGetKey(window.get(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        c.SetCameraSpeed(10.f * window.getDT());
    if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
        c.CameraForward();
    if (glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS)
        c.CameraBackward();
    if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
        c.CameraLeft();
    if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
        c.CameraRight();
    if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.get(), GLFW_TRUE);
    if (glfwGetKey(window.get(), GLFW_KEY_1) == GLFW_PRESS) {
        load = false;
        loadedObject = "res/ak47.obj";
    }
    if (glfwGetKey(window.get(), GLFW_KEY_2) == GLFW_PRESS) {
    load = false;
        loadedObject = "res/teapot.obj";
    }
    if (glfwGetKey(window.get(), GLFW_KEY_3) == GLFW_PRESS) {
    load = false;
        loadedObject = "res/fish.obj";
    }
}

void mouseFunc() {
    double xpos, ypos;
    glfwGetCursorPos(window.get(), &xpos, &ypos);
    c.updateMouse(xpos, ypos);
}

 std::vector<ColouredVertex> vertices;
 GameObject object;
 Mesh m;

void renderFunc() {
    if(load == false) {
        loader.LoadFile(loadedObject.c_str());
        vertices.clear();
        for(int i = 0; i < loader.LoadedVertices.size(); i++) {
            vertices.push_back(ColouredVertex(loader.LoadedVertices[i].Position.X,
            loader.LoadedVertices[i].Position.Y,loader.LoadedVertices[i].Position.Z,1.0f, 0.84f, 0.0f));
        }
        m.Update(vertices);
        object.Update(&sp, &m);
        load = true;
    }
    object.UploadPV(c.GetPV());
    object.SetRotation(window.getDT(), glm::vec3(0,1,0));
    object.DrawObject();
}

void guiFunc() {
    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
    std::string data = std::string("X: ");
    data += std::to_string(c.GetPosition().x);
    data += " Y: ";
    data += std::to_string(c.GetPosition().y);
    data += " Z: ";
    data += std::to_string(c.GetPosition().z);
    ImGui::Text(data.c_str());
    data = "";
    data = std::string("Pitch: ");
    data += std::to_string(c.getPitch());
    data += " Yaw: ";
    data += std::to_string(c.getYaw());
    ImGui::Text(data.c_str());
    ImGui::Text("Camera Speed: %f", c.getCameraSpeed());
    ImGui::Text("Object Rotation Speed: %f", glfwGetTime());
    data = "Loaded Object: ";
    data += loadedObject;
    ImGui::Text(data.c_str());
    ImGui::Text("Press 1 for ak47, 2 for teapot, 3 for fish");
}

int main() {
    window.setRenderCallback(renderFunc);
    window.setKeyboardCallback(inputFunc);
    window.setMouseCallback(mouseFunc);
    window.setGUICallback(guiFunc);
    ImGui_ImplGlfwGL3_Init(window.get(), true);
    window.Run();
}