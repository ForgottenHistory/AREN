#include "AMath.h"

float ASin(float x)
{
    return std::sin(x);
}

float ACos(float x)
{
    return std::cos(x);
}

float ATan(float x)
{
    return std::atan(x);
}

float ATan2(float y, float x)
{
    return std::atan2(y, x);
}

float ASqrt(float x)
{
    return std::sqrt(x);
}

float APow(float x, float y)
{
    return std::pow(x, y);
}

float RadiansToDegrees(float radians)
{
    return radians * 180.0f / 3.14159265359f;
}

float DegreesToRadians(float degrees)
{
    return degrees * 3.14159265359f / 180.0f;
}
