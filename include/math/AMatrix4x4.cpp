#include "AMatrix4x4.h"

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

AMatrix4x4 AMatrix4x4::Identity()
{
    AMatrix4x4 identity;

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
