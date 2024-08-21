#include "Mesh.h"

#include <utility>


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->textures = std::move(textures);

    setupMesh();
}

Mesh::~Mesh() {}

void Mesh::draw(Shader &shader) {}

void Mesh::setupMesh() {}
