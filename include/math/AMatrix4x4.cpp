#include "AMatrix4x4.h"
#include "math/avec3.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMatrix4x4::AMatrix4x4()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            m[i][j] = 0.0f;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMatrix4x4::AMatrix4x4(float value)
{
    for (int i = 0; i < 4; ++i)
    {
        m[i][i] = value;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMatrix4x4::AMatrix4x4(float& m00, float& m01, float& m02, float& m03,
               float& m10, float& m11, float& m12, float& m13,
               float& m20, float& m21, float& m22, float& m23,
               float& m30, float& m31, float& m32, float& m33)
               {
                    // Row 1
                    m[0][0] = m00;
                    m[0][1] = m01;
                    m[0][2] = m02;
                    m[0][3] = m03;

                    // Row 2
                    m[1][0] = m10;
                    m[1][1] = m11;
                    m[1][2] = m12;
                    m[1][3] = m13;

                    // Row 3

                    m[2][0] = m20;
                    m[2][1] = m21;
                    m[2][2] = m22;
                    m[2][3] = m23;

                    // Row 4
                    m[3][0] = m30;
                    m[3][1] = m31;
                    m[3][2] = m32;
                    m[3][3] = m33;
               }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMatrix4x4::AMatrix4x4(const AVec3& translation, const AVec3& rotation, const AVec3& scale)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMatrix4x4::AMatrix4x4(const glm::mat4& glmMatrix) 
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            m[i][j] = glmMatrix[i][j];
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMatrix4x4 AMatrix4x4::Identity()
{
    AMatrix4x4 identity = AMatrix4x4();

    for (int i = 0; i < 4; ++i)
    {
        identity.m[i][i] = 1.0f;
    }

    return identity;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMatrix4x4 AMatrix4x4::operator*(const AMatrix4x4& other) const
{
    AMatrix4x4 result;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMatrix4x4& AMatrix4x4::operator*=(const AMatrix4x4& other)
{
    AMatrix4x4 result = *this * other;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            m[i][j] = result.m[i][j];
        }
    }

    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

glm::mat4 AMatrix4x4::ToGLM() const
{
    return glm::make_mat4(&m[0][0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
