#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) 800 / (float)600, 0.1f, 100.0f);
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    glm::mat4 view;
    float cameraSpeed = 2.5f;
    bool firstMouse = true;
float yaw   = -90.0f;	
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;
public:
    Camera() {
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }
    ~Camera() {}
    glm::mat4 GetPV() {
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        return Projection * view;
    }
    glm::vec3 GetPosition() {
        return cameraPos;
    }
    float getCameraSpeed() {
        return cameraSpeed;
    }
    float getYaw() {
        return yaw;
    }
    float getPitch() {
        return pitch;
    }
    void updateMouse(double xpos, double ypos)
    {
        if(firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
    
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; 
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.2;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
    }  
    void SetCameraSpeed(float cs) {
        cameraSpeed = cs;
    }
    void CameraForward() {
        cameraPos += cameraSpeed * cameraFront;
    }
    void CameraBackward() {
        cameraPos -= cameraSpeed * cameraFront;
    }
    void CameraLeft() {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    void CameraRight() {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
};