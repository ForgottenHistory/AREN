#pragma once
#include "acomponent.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MoveWithTime : public Component
{
public:

    enum class MoveType
    {
        SINTIME,
        COSTIME,
        TANTIME,
        SIZE
    };

    MoveWithTime(MoveType _moveType);
    MoveWithTime(float _speed, float _amplitude, MoveType _moveType);

    void Update() override;

    float speed;
    float amplitude;
    float time;
    MoveType moveType;

    bool lockX = false;
    bool lockY = false;
    bool lockZ = false;
private:
    glm::vec3 CalculatePosition(glm::vec3 _pos);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
