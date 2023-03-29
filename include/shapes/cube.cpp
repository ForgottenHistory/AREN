#include "cube.h"

Cube::Cube()
    : width(1.0f), height(1.0f), depth(1.0f) {
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Cube::Setup() {
    setupBuffers();
}

void Cube::Render() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

std::vector<GLfloat> Cube::generateVertexData() const {
    std::vector<GLfloat> vertices = {
        -width / 2, -height / 2, -depth / 2,
         width / 2, -height / 2, -depth / 2,
         width / 2,  height / 2, -depth / 2,
        -width / 2,  height / 2, -depth / 2,
        -width / 2, -height / 2,  depth / 2,
         width / 2, -height / 2,  depth / 2,
         width / 2,  height / 2,  depth / 2,
        -width / 2,  height / 2,  depth / 2,
    };

    return vertices;
}

std::vector<GLuint> Cube::generateIndexData() const {
    std::vector<GLuint> indices = {
        0, 1, 2, 2, 3, 0,
        1, 5, 6, 6, 2, 1,
        5, 4, 7, 7, 6, 5,
        4, 0, 3, 3, 7, 4,
        3, 2, 6, 6, 7, 3,
        4, 5, 1, 1, 0, 4
    };

    return indices;
}
