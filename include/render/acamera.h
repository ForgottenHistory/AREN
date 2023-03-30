#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ACamera
{
public:
    // Constructor
    ACamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f,
           float pitch = 0.0f);

    // Accessor functions
    const glm::mat4 &getViewMatrix() const;
    const glm::mat4 &getProjectionMatrix() const;

    // Camera movement functions
    void setPosition(const glm::vec3 &position);
    void setTarget(const glm::vec3 &target);
    void setUpVector(const glm::vec3 &up);
    void setAspectRatio(float aspectRatio);
    void setFieldOfView(float fov);
    void setNearPlane(float nearPlane);
    void setFarPlane(float farPlane);

    void updateViewMatrix();
    void updateProjectionMatrix();

private:
    // Projection properties
    float m_aspectRatio;
    float m_fov;
    float m_nearPlane;
    float m_farPlane;

    // Matrices
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
};

#endif // CAMERA_H
