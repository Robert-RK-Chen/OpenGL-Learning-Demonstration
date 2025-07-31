#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer
{
private:

public:
    Renderer();
    ~Renderer();

    void Clear() const;
    void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
};