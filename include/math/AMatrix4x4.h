#pragma once

class AMatrix4x4
{
public:
    float m[4][4];

    AMatrix4x4();

    // Identity matrix
    static AMatrix4x4 Identity();

    // Matrix multiplication
    AMatrix4x4 operator*(const AMatrix4x4& other) const;

    // Compound assignment operator for matrix multiplication
    AMatrix4x4& operator*=(const AMatrix4x4& other);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
