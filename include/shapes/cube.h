#pragma once

#include "ashapes.h"

class Cube : public APrimitiveShape {
public:
    Cube();
    ~Cube();

    void Setup() override;
    void Render() override;

protected:

    virtual void SetupBuffers() override;

    std::vector<GLfloat> GenerateVertexData() const override;
    std::vector<GLuint> GenerateIndexData() const override;

    // Dimensions of the cube.
    float width;
    float height;
    float depth;
};
