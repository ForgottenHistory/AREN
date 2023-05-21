#pragma once
#include "glmpch.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AVec3 {
public:
    // Constructors
    AVec3() : x(0.0f), y(0.0f), z(0.0f) {}
    AVec3(float x, float y, float z) : x(x), y(y), z(z) {}
    AVec3(float x) : x(x), y(x), z(x) {}
    AVec3(glm::vec3 glmVec) : x(glmVec.x), y(glmVec.y), z(glmVec.z) {}

    // Basic arithmetic operations
    AVec3 operator+(const AVec3& other) const;
    AVec3 operator-(const AVec3& other) const;
    AVec3 operator*(float scalar) const;
    AVec3 operator/(float scalar) const;

    // Compound assignment operators
    AVec3& operator+=(const AVec3& other);
    AVec3& operator-=(const AVec3& other);
    AVec3& operator*=(float scalar);
    AVec3& operator/=(float scalar);
    AVec3& operator=(AVec3 other);

    // Dot product
    float dot(const AVec3& other) const;

    // Cross product
    AVec3 cross(const AVec3& other) const;
    // Magnitude
    float magnitude() const;
    // Normalization
    AVec3 normalize() const;

    glm::vec3 to_glm() const;
    
    // Members
    float x, y, z;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
