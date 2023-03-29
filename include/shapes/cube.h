#pragma once

#include "ashapes.h"

class Cube : public APrimitiveShape {
public:
    Cube();
    ~Cube();

    void Setup() override;
    void Render() override;

protected:

    virtual void setupBuffers() override;

    std::vector<GLfloat> generateVertexData() const override;
    std::vector<GLuint> generateIndexData() const override;

    // Dimensions of the cube.
    float width;
    float height;
    float depth;
};
