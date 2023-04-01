#include <debug/test.h>
#include "test.h"
#include "time.h"
#include "aobject.h"

TestMovement::~TestMovement()
{
}

void TestMovement::Update()
{
    // Get the owner object and move it with sinTime from Time class
    ATransform* trans = owner->GetComponent<ATransform>();
    glm::vec3 pos = trans->GetPosition();

    pos.x = Time::sinTime * 1.0f;
    pos.z = Time::cosTime * 1.0f;

    trans->SetPosition(pos);
}