#pragma once
#include <glfw/glfw3.h>
#include <GL/glew.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

class Window {
private:
    GLFWwindow* window;
    void (*renderCallback)(void);
    void (*keyboardCallback)(void);
    void (*mouseCallback)(void);
    void (*guiCallback)(void);
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
public:
    Window() {
        glfwInit();
        glfwWindowHint(GLFW_SAMPLES, 16);
        window = glfwCreateWindow(800, 600, "IMDCGP208-17S1D Programming For Graphics", NULL, NULL);
        glfwMakeContextCurrent(window);
        glewInit();
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    }
    void setRenderCallback(void (*cb)(void)) {
        renderCallback = cb;
    }
    void setKeyboardCallback(void (*ic)(void)) {
        keyboardCallback = ic;
    }
    void setMouseCallback(void (*mc)(void)) {
        mouseCallback = mc;
    }
    void setGUICallback(void (*gc)(void)) {
        guiCallback = gc;
    }
    GLFWwindow* get() {
        return window;
    }
    float getDT() {
        return deltaTime;
    }
    void Run() {
        while(!glfwWindowShouldClose(window)) {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;  

            glfwPollEvents();
            ImGui_ImplGlfwGL3_NewFrame();
            mouseCallback();
            keyboardCallback();

            ImGuiWindowFlags window_flags = 0;
            window_flags |= ImGuiWindowFlags_NoTitleBar;
            window_flags |= ImGuiWindowFlags_NoScrollbar;
            window_flags |= ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoResize;
            window_flags |= ImGuiWindowFlags_NoCollapse;

            bool p_open = true;
            ImGui::SetNextWindowSize(ImVec2(800, 600));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("Window", &p_open, window_flags);
            guiCallback();
            ImGui::End();

            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            renderCallback();
            ImGui::Render();
            glfwSwapBuffers(window);
        }
    }
};