#pragma once
#include <glm/glm.hpp>

typedef glm::vec3 vec3;

class AObject {
public:
    AObject();
    ~AObject();

    void Update();
    void Render();

    // Getters
    const vec3& GetPosition() const;
    const vec3& GetRotation() const;
    const vec3& GetScale() const;

    // Setters
    void SetPosition(const vec3& newPosition);
    void SetRotation(const vec3& newRotation);
    void SetScale(const vec3& newScale);

    // Transformations
    void Translate(const vec3& translation);
    void Rotate(const vec3& rotation);
    void Scale(const vec3& scale);

    vec3 position;
    vec3 rotation;
    vec3 scale;

};
