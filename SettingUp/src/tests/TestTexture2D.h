#pragma once

#include "Test.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <IndexBuffer.h>
#include <memory>
#include <Shader.h>
#include <VertexArray.h>
#include <VertexBuffer.h>

namespace test
{
    class TestTexture2D : public Test
    {
    private:
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
        std::unique_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        glm::mat4 m_Proj, m_View;
        glm::vec3 m_TranslationA, m_TranslationB;

    public:
        TestTexture2D();
        ~TestTexture2D();
        void OnUpdate(float dateTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    };
}