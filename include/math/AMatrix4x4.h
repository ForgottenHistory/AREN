#pragma once
#include "glmpch.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AVec3;
class AMatrix4x4
{
public:
    float m[4][4];

    AMatrix4x4();
    AMatrix4x4(float value);
    AMatrix4x4(float& m00, float& m01, float& m02, float& m03,
               float& m10, float& m11, float& m12, float& m13,
               float& m20, float& m21, float& m22, float& m23,
               float& m30, float& m31, float& m32, float& m33);
    AMatrix4x4(const AVec3& translation, const AVec3& rotation, const AVec3& scale);
    AMatrix4x4(const glm::mat4& glmMatrix);

    // Identity matrix
    static AMatrix4x4 Identity();

    // Matrix multiplication
    AMatrix4x4 operator*(const AMatrix4x4& other) const;

    // Compound assignment operator for matrix multiplication
    AMatrix4x4& operator*=(const AMatrix4x4& other);

    // Conversion to GLM matrix
    glm::mat4 ToGLM() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
