#include "GLCall.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "testTexture2D.h"
#include <GL/glew.h>
#include <glm/fwd.hpp>
#include <IndexBuffer.h>
#include <memory>
#include <Renderer.h>
#include <Shader.h>
#include <Texture.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>

namespace test
{
    TestTexture2D::TestTexture2D() :
        m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0),
        m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
    {
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,    // point 1
             50.0f, -50.0f, 1.0f, 0.0f,    // point 2
             50.0f,  50.0f, 1.0f, 1.0f,    // point 3
            -50.0f,  50.0f, 0.0f, 1.0f     // point 4
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);
        m_Shader = std::make_unique<Shader>("res/shaders/basic.shader");
        m_Texture = std::make_unique<Texture>("res/textures/icon.png");
        m_VertexArray = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        m_Shader->SetUniform1i("u_Texture", 0);
    }

    TestTexture2D::~TestTexture2D()
    {
        GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    }

    void TestTexture2D::OnUpdate(float dateTime)
    {
    }

    void TestTexture2D::OnRender()
    {
        GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
        Renderer renderer;
        m_Texture->Bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
        }
    }

    void TestTexture2D::OnImGuiRender()
    {
        ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
        ImGui::Text("App Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
} 