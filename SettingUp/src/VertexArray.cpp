#include "GLCall.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <GL/glew.h>

VertexArray::VertexArray()
{
    GLCALL(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCALL(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) const
{
    Bind();
    vertexBuffer.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;

    // ���ò���
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCALL(glEnableVertexAttribArray(i));
        GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    GLCALL(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCALL(glBindVertexArray(0));
}