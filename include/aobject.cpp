#include "aobject.h"

AObject::AObject()
    : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f)
{
}

AObject::~AObject()
{
}

void AObject::Update()
{
}

void AObject::Render()
{
}

const vec3 &AObject::GetPosition() const
{
    return position;
}

const vec3 &AObject::GetRotation() const
{
    return rotation;
}

const vec3 &AObject::GetScale() const
{
    return scale;
}

void AObject::SetPosition(const vec3 &newPosition)
{
    position = newPosition;
}

void AObject::SetRotation(const vec3 &newRotation)
{
    rotation = newRotation;
}

void AObject::SetScale(const vec3 &newScale)
{
    scale = newScale;
}

void AObject::Translate(const vec3 &translation)
{
    position += translation;
}

void AObject::Rotate(const vec3 &rotationDelta)
{
    rotation += rotationDelta;
}

void AObject::Scale(const vec3 &scaleDelta)
{
    scale *= scaleDelta;
}
