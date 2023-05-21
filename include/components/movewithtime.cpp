#include "movewithtime.h"
#include "time.h"
#include "aobject.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MoveWithTime::MoveWithTime(MoveType _moveType)
{
    speed = 1.0f;
    amplitude = 1.0f;
    time = 0.0f;
    moveType = _moveType;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MoveWithTime::MoveWithTime(float _speed, float _amplitude, MoveType _moveType)
{
    speed = _speed;
    amplitude = _amplitude;
    time = 0.0f;
    moveType = _moveType;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MoveWithTime::Update()
{
    time += Time::deltaTime;
    ATransform *transform = owner->GetComponent<ATransform>();
    transform->SetPosition(CalculatePosition(transform->GetPosition()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

glm::vec3 MoveWithTime::CalculatePosition(glm::vec3 _pos)
{
    switch (moveType)
    {
    case MoveType::SINTIME:
       if( !lockX )
            _pos.x = sin(time * speed) * amplitude;
        if( !lockY )
            _pos.y = sin(time * speed) * amplitude;
        if( !lockZ )
            _pos.z = sin(time * speed) * amplitude;
        break;
    case MoveType::COSTIME:
        if( !lockX )
            _pos.x = cos(time * speed) * amplitude;
        if( !lockY )
            _pos.y = cos(time * speed) * amplitude;
        if( !lockZ )
            _pos.z = cos(time * speed) * amplitude;
        break;
    case MoveType::TANTIME:
        if( !lockX )
            _pos.x = tan(time * speed) * amplitude;
        if( !lockY )
            _pos.y = tan(time * speed) * amplitude;
        if( !lockZ )
            _pos.z = tan(time * speed) * amplitude;
        break;
    default:
        break;
    }

    return _pos;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
