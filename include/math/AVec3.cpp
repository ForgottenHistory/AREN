#include "AVec3.h"

AVec3 AVec3::operator+(const AVec3& other) const
{
    return AVec3(x + other.x, y + other.y, z + other.z);
}

AVec3 AVec3::operator-(const AVec3& other) const
{
    return AVec3(x-  other.x, y - other.y, z - other.z);
}

AVec3 AVec3::operator*(float scalar) const
{
    return AVec3(x * scalar, y * scalar, z * scalar);
}

AVec3 AVec3::operator/(float scalar) const
{
    return AVec3(x / scalar, y / scalar, z / scalar);
}

AVec3& AVec3::operator+=(const AVec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

AVec3& AVec3::operator-=(const AVec3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

AVec3& AVec3::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

AVec3& AVec3::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

AVec3& AVec3::operator=(AVec3 other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

// Dot product
float AVec3::dot(const AVec3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

// Cross product
AVec3 AVec3::cross(const AVec3& other) const
{
    return AVec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x);
}

// Magnitude
float AVec3::magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

// Normalization
AVec3 AVec3::normalize() const
{
    float mag = magnitude();
    return AVec3(x / mag, y / mag, z / mag);
}

glm::vec3 AVec3::to_glm() const
{
    return glm::vec3(x, y, z);
}